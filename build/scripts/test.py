# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: test.py
# Copyright (c) Nick De Breuck 2022
#
# ============================================

import argparse
import required_tools
import util
import os
import task_raii_printing
import rex_json
import coverage_tests
import traceback
import diagnostics
import shutil

from pathlib import Path

root_path = util.find_root()
tool_paths = required_tools.tool_paths
settings = rex_json.load_file(os.path.join(root_path, "build", "config", "settings.json"))
__pass_results = {}

def __run_include_what_you_use(fixIncludes = False):
  task_print = task_raii_printing.TaskRaiiPrint("running include-what-you-use")

  intermediate_directory = os.path.join(root_path, settings["intermediate_directory"], settings["build_folder"])
  result = util.find_all_files_in_folder(intermediate_directory, "compile_commands.json")
    
  for compiler_db in result:
    iwyu_path = tool_paths["include_what_you_use_path"]
    iwyu_tool_path = os.path.join(Path(iwyu_path).parent, "iwyu_tool.py")
    fix_includes_path = os.path.join(Path(iwyu_path).parent, "fix_includes.py")
    compiler_db_folder = Path(compiler_db).parent
    output_path = os.path.join(compiler_db_folder, "iwyu_output.log")
    os.system(f"py {iwyu_tool_path} -v -p={compiler_db_folder} > {output_path}") # needs to use os.system or iwyu will parse the command incorrectly
    if fixIncludes:
      os.system(f"py {fix_includes_path} --update_comments --safe_headers < {output_path}")

  return 0

def __run_clang_tidy():
  task_print = task_raii_printing.TaskRaiiPrint("running clang-tidy")

  intermediate_directory = os.path.join(root_path, settings["intermediate_directory"], settings["build_folder"])
  result = util.find_all_files_in_folder(intermediate_directory, "compile_commands.json")

  rc = 0
  for compiler_db in result:
    script_path = os.path.dirname(__file__)
    clang_tidy_path = tool_paths["clang_tidy_path"]
    clang_apply_replacements_path = tool_paths["clang_apply_replacements_path"]
    compiler_db_folder = Path(compiler_db).parent
    config_file_path = f"{root_path}/source/.clang-tidy_first_pass"
    proc = util.run_subprocess(f"py {script_path}/run_clang_tidy.py -clang-tidy-binary={clang_tidy_path} -clang-apply-replacements-binary={clang_apply_replacements_path} -config-file={config_file_path} -p={compiler_db_folder} -header-filter=.* -quiet -fix") # force clang compiler, as clang-tools expect it
    new_rc = util.wait_for_process(proc)
    if new_rc != 0:
      diagnostics.log_err(f"clang-tidy failed for {compiler_db}")
      diagnostics.log_err(f"config file: {config_file_path}")
    rc |= new_rc

  return rc

def __generate_tests():
  task_print = task_raii_printing.TaskRaiiPrint("generating unit test projects")
  return __generate_test_files("/generateTests")

def __build_tests():
  task_print = task_raii_printing.TaskRaiiPrint("building tests")
  return __build_test_files(os.path.join(root_path, settings["intermediate_directory"], settings["tests_folder"], settings["build_folder"]), "*.ninja")

def __run_unit_tests():
  task_print = task_raii_printing.TaskRaiiPrint("running unit tests")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_directory"], settings["tests_folder"], settings["build_folder"]))
  
  rc = 0
  for program in unit_test_programs:
    diagnostics.log_info(f"running: {Path(program).name}")
    proc = util.run_subprocess(program)
    new_rc = util.wait_for_process(proc)
    if new_rc != 0:
      diagnostics.log_err(f"unit test failed for {program}") # use full path to avoid ambiguity
    rc |= new_rc

  return rc

def __generate_coverage():
  task_print = task_raii_printing.TaskRaiiPrint("generating coverage code")
  return __generate_test_files("/generateTests /enableCoverage")

def __build_coverage():
  task_print = task_raii_printing.TaskRaiiPrint("building coverage code")
  return __build_test_files(root_path, "*_coverage.ninja")

def __run_coverage():
  task_print = task_raii_printing.TaskRaiiPrint("running coverage")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_directory"], settings["coverage_folder"]))

  rc = 0
  for program in unit_test_programs:
    diagnostics.log_info(f"running: {Path(program).name}")
    os.environ["LLVM_PROFILE_FILE"] = __get_coverage_rawdata_filename(program) # this is what llvm uses to set the raw data filename for the coverage data
    proc = util.run_subprocess(program)
    new_rc = util.wait_for_process(proc)
    if new_rc != 0:
      diagnostics.log_err(f"unit test failed for {program}") # use full path to avoid ambiguity
    rc |= new_rc

  return unit_test_programs

def __relocate_coverage_data(programsRun : list[str]):
  task_print = task_raii_printing.TaskRaiiPrint("relocating coverage files")
  data_files = []

  for program in programsRun:
    coverage_rawdata_filename = __get_coverage_rawdata_filename(program)
    newPath = os.path.join(Path(program).parent, coverage_rawdata_filename)
    if (os.path.exists(newPath)):
      os.remove(newPath)
    os.rename(coverage_rawdata_filename, newPath)
    data_files.append(newPath)
    
  return data_files

def __index_rawdata_files(rawdataFiles : list[str]):
  task_print = task_raii_printing.TaskRaiiPrint("indexing rawdata files")
  output_files = []

  for file in rawdataFiles:
    output_files.append(coverage_tests.index_rawdata(file))

  return output_files

def __create_coverage_reports(programsRun, indexdataFiles):
  task_print = task_raii_printing.TaskRaiiPrint("creating coverage reports")

  rc = 0
  for index in range(len(programsRun)):
    program = programsRun[index]
    indexdata_file = indexdataFiles[index]

    if Path(program).stem != Path(indexdata_file).stem:
      rc = 1
      diagnostics.log_err(f"program stem doesn't match coverage file stem: {Path(program).stem} != {Path(indexdata_file).stem}")

    coverage_tests.create_line_oriented_report(program, indexdata_file)
    coverage_tests.create_file_level_summary(program, indexdata_file)

  return rc

def __parse_coverage_reports(indexdataFiles):
  task_print = task_raii_printing.TaskRaiiPrint("parsing coverage reports")

  rc = 0
  for indexdata_file in indexdataFiles:
    report_filename = coverage_tests.file_level_summary_filename(indexdata_file)
    rc |= coverage_tests.parse_file_summary(report_filename)

  return rc

def __get_coverage_rawdata_filename(program : str):
  return f"{Path(program).stem}.profraw"

def __generate_address_sanitizer():
  task_print = task_raii_printing.TaskRaiiPrint("generating address sanitizer code")
  return __generate_test_files("/generateTests /enableAddressSanitizer")

def __build_address_sanitizer():
  task_print = task_raii_printing.TaskRaiiPrint("building address sanitizer code")
  return __build_test_files(root_path, "*_asan.ninja")

def __run_address_sanitizer():
  task_print = task_raii_printing.TaskRaiiPrint("running address sanitizer tests")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_directory"], settings["tests_folder"], "asan"))
  
  rc = 0
  for program in unit_test_programs:
    diagnostics.log_info(f"running: {Path(program).name}")
    log_folder_path = Path(program).parent
    log_folder = log_folder_path.as_posix()
    
    # for some reason, setting an absolute path for the log folder doesn't work
    # so we have to set the working directory of the program to where it's located so the log file will be there as well
    # ASAN_OPTIONS common flags: https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
    # ASAN_OPTIONS flags: https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
    asan_options = f"print_stacktrace=1:log_path=asan.log"
    os.environ["ASAN_OPTIONS"] = asan_options # print callstacks and save to log file
    
    proc = util.run_subprocess_with_working_dir(program, log_folder)
    new_rc = util.wait_for_process(proc)
    log_file_path = os.path.join(log_folder, f"asan.log.{proc.pid}")
    if new_rc != 0 or os.path.exists(log_file_path):
      diagnostics.log_err(f"address sanitizer failed for {program}") # use full path to avoid ambiguity
      diagnostics.log_err(f"for more info, please check: {log_file_path}")
      new_rc = 1
    rc |= new_rc

  return rc

def __generate_undefined_behavior_sanitizer():
  task_print = task_raii_printing.TaskRaiiPrint("generating undefined behavior sanitizer code")
  return __generate_test_files("/generateTests /enableUBSanitizer")

def __build_undefined_behavior_sanitizer():
  task_print = task_raii_printing.TaskRaiiPrint("building undefined behavior sanitizer code")
  return __build_test_files(root_path, "*_ubsan.ninja")

def __run_undefined_behavior_sanitizer():
  task_print = task_raii_printing.TaskRaiiPrint("running undefined behavior sanitizer tests")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_directory"], settings["tests_folder"], "ubsan"))
  
  rc = 0
  for program in unit_test_programs:
    diagnostics.log_info(f"running: {Path(program).name}")
    log_folder_path = Path(program).parent
    log_folder = log_folder_path.as_posix()
    
    # for some reason, setting an absolute path for the log folder doesn't work
    # so we have to set the working directory of the program to where it's located so the log file will be there as well
    # UBSAN_OPTIONS common flags: https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
    ubsan_options = f"print_stacktrace=1:log_path=ubsan.log"
    os.environ["UBSAN_OPTIONS"] = ubsan_options # print callstacks and save to log file
    proc = util.run_subprocess_with_working_dir(program, log_folder)
    new_rc = util.wait_for_process(proc)
    log_file_path = os.path.join(log_folder, f"ubsan.log.{proc.pid}")
    if new_rc != 0 or os.path.exists(log_file_path): # if there's a ubsan.log.pid created, the tool found issues
      diagnostics.log_err(f"undefined behavior sanitizer failed for {program}") # use full path to avoid ambiguity
      diagnostics.log_err(f"for more info, please check: {log_file_path}")
      new_rc = 1
    rc |= new_rc

  return rc

def __generate_fuzzy_testing():
  task_print = task_raii_printing.TaskRaiiPrint("generating fuzzy testing code")
  return __generate_test_files("/enableFuzzyTesting")

def __build_fuzzy_testing():
  task_print = task_raii_printing.TaskRaiiPrint("building fuzzy testing code")
  return __build_test_files(root_path, "*_fuzzy.ninja")

def __run_fuzzy_testing():
  task_print = task_raii_printing.TaskRaiiPrint("running fuzzy tests")
  fuzzy_programs = __find_test_programs(os.path.join(settings["intermediate_directory"], settings["tests_folder"], "fuzzy"))
  
  rc = 0
  for program in fuzzy_programs:
    diagnostics.log_info(f"running: {Path(program).name}")
    log_folder_path = Path(program).parent
    log_folder = log_folder_path.as_posix()
    
    # for some reason, setting an absolute path for the log folder doesn't work
    # so we have to set the working directory of the program to where it's located so the log file will be there as well
    # Can't use both ASAN as well as UBSAN options, so we'll set the same for both and hope that works
    # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94328
    # https://stackoverflow.com/questions/60774638/logging-control-for-address-sanitizer-plus-undefined-behavior-sanitizer
    asan_options = f"print_stacktrace=1:log_path=fuzzy.log"
    ubsan_options = f"print_stacktrace=1:log_path=fuzzy.log"
    os.environ["ASAN_OPTIONS"] = asan_options # print callstacks and save to log file
    os.environ["UBSAN_OPTIONS"] = ubsan_options # print callstacks and save to log file
    num_runs = 10000 # we'll run 10'000 fuzzy tests, should be more than enough
    proc = util.run_subprocess_with_working_dir(f"{program} -runs={num_runs}", log_folder)
    new_rc = util.wait_for_process(proc)
    log_file_path = os.path.join(log_folder, f"fuzzy.log.{proc.pid}")
    if new_rc != 0 or os.path.exists(log_file_path): # if there's a ubsan.log.pid created, the tool found issues
      diagnostics.log_err(f"fuzzy testing failed for {program}") # use full path to avoid ambiguity
      if os.path.exists(log_file_path):
        diagnostics.log_err(f"issues found while fuzzing!")
        diagnostics.log_err(f"for more info, please check: {log_file_path}")
      new_rc = 1
    rc |= new_rc

  return rc

def __generate_test_files(sharpmakeArgs):
  generate_script = os.path.join(root_path, "build", "scripts", "generate.py")
  sharpmake_main_path = os.path.join(root_path, 'build', 'sharpmake', 'src', 'main.sharpmake.cs')
  proc = util.run_subprocess(f"py {generate_script} -sharpmake_main={sharpmake_main_path} -sharpmake_args=\"{sharpmakeArgs}\"")
  return util.wait_for_process(proc)

ninja_rc = True
def __ninja_output_callback(output):
  for line in iter(output.readline, b''):
    new_line : str = line.decode('UTF-8')
    if new_line.endswith('\n'):
      new_line = new_line.removesuffix('\n')

    if "FAILED:" in new_line:
      global ninja_rc
      ninja_rc = 1
      diagnostics.log_err(new_line)
    else:
      diagnostics.log_no_color(new_line)

def __run_ninja_process(command):
  ninja_path = tool_paths["ninja_path"]
  global ninja_rc
  ninja_rc = 0
  proc = util.run_subprocess_with_callback(f"{ninja_path} {command}", __ninja_output_callback)
  util.wait_for_process(proc)
  return ninja_rc

def __build_test_files(folder, ninjaFileRegex):
  ninja_files = util.find_all_files_in_folder(folder, ninjaFileRegex)
  rc = 0
  for ninja_file in ninja_files:
    new_rc = __run_ninja_process(f"-f {ninja_file}")
    if new_rc != 0:
      diagnostics.log_err(f"Failed to build {ninja_file}")
    rc |= new_rc

  return rc

def __find_test_programs(folder):
  intermediate_directory = os.path.join(folder)
  diagnostics.log_info(f"looking for executables in {os.path.join(root_path, intermediate_directory)}")
  result = util.find_all_files_in_folder(os.path.join(root_path, intermediate_directory), "*")
  coverage_programs = []
  for res in result:
    if util.is_executable(res):
      coverage_programs.append(res.absolute())

  return coverage_programs

def __include_what_you_use_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __run_include_what_you_use()

  if rc != 0:
    diagnostics.log_err(f"include-what-you-use pass failed")

  __pass_results["include-what-you-use"] = rc

def __clang_tidy_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __run_clang_tidy() # works
  if rc != 0:
    diagnostics.log_err(f"clang-tidy pass failed")

  __pass_results["clang-tidy"] = rc

def __unit_tests_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_tests() # works
  if rc != 0:
    diagnostics.log_err(f"failed to generate tests")
  __pass_results["unit tests generation"] = rc

  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_tests() # works
  if rc != 0:
    diagnostics.log_err(f"failed to build tests")
  __pass_results["unit tests building"] = rc

  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_unit_tests() # works
  if rc != 0:
    diagnostics.log_err(f"unit tests failed")
  __pass_results["unit tests result"] = rc

def __coverage_tests_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_coverage() # works
  if rc != 0:
    diagnostics.log_err(f"failed to generate coverage")
  __pass_results["coverage generation"] = rc

  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __build_coverage() # works
  if rc != 0:
    diagnostics.log_err(f"failed to build coverage")
  __pass_results["coverage building"] = rc

  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  programs_run = __run_coverage() # works
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rawdata_files = __relocate_coverage_data(programs_run) # works
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  indexdata_files = __index_rawdata_files(rawdata_files) # works
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __create_coverage_reports(programs_run, indexdata_files) # works
  if rc != 0:
    diagnostics.log_err(f"failed to create coverage reports")
  __pass_results["coverage report creation"] = rc

  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __parse_coverage_reports(indexdata_files) # works
  if rc != 0:
    diagnostics.log_err(f"Not all the code was covered")
  __pass_results["coverage report result"] = rc

def __asan_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_address_sanitizer() # works
  if rc != 0:
    diagnostics.log_err(f"failed to generate asan code")
  __pass_results["address sanitizer generation"] = rc

  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_address_sanitizer() # works
  if rc != 0:
    diagnostics.log_err(f"failed to build asan code")
  __pass_results["address sanitizer building"] = rc
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_address_sanitizer() # works
  if rc != 0:
    diagnostics.log_err(f"invalid code found with asan")
  __pass_results["address sanitizer result"] = rc

def __ubsan_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_undefined_behavior_sanitizer() # works
  if rc != 0:
    diagnostics.log_err(f"failed to generate ubsan code")
  __pass_results["undefined behavior sanitizer generation"] = rc
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_undefined_behavior_sanitizer() # works
  if rc != 0:
    diagnostics.log_err(f"failed to build ubsan code")
  __pass_results["undefined behavior sanitizer building"] = rc
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_undefined_behavior_sanitizer() # works
  if rc != 0:
    diagnostics.log_err(f"invalid code found with ubsan")
  __pass_results["undefined behavior sanitizer result"] = rc

def __fuzzy_testing_pass():
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_fuzzy_testing() # works
  if rc != 0:
    diagnostics.log_err(f"failed to generate fuzzy code")
  __pass_results["fuzzy testing generation"] = rc
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_fuzzy_testing() # works
  if rc != 0:
    diagnostics.log_err(f"failed to build fuzzy code")
  __pass_results["fuzzy testing building"] = rc
  
  diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_fuzzy_testing() # works
  if rc != 0:
    diagnostics.log_err(f"invalid code found with fuzzy")
  __pass_results["fuzzy testing result"] = rc

def __clean():
  intermediate_tests_path = os.path.join(root_path, settings["intermediate_directory"], settings["tests_folder"])
  if os.path.exists(intermediate_tests_path):
    shutil.rmtree(intermediate_tests_path)

def run():
  try:
    parser = argparse.ArgumentParser()
    parser.add_argument("-clean", help="clean run, as if run for the first time", action="store_true")
    args,unknown = parser.parse_known_args()
        
    if args.clean:
      __clean()

    # __include_what_you_use_pass()
    # __clang_tidy_pass()
    # __unit_tests_pass()
    __coverage_tests_pass()
    # __asan_pass()
    # __ubsan_pass()
    # __fuzzy_testing_pass()

  except Exception as Ex:
    traceback.print_exc()
    diagnostics.log_err(f"exception: {Ex}")

  diagnostics.log_no_color("")
  diagnostics.log_info("Summary Report")
  diagnostics.log_no_color("--------------------------------------")
  for key in __pass_results:
    result = __pass_results[key]

    if result == 0:
      diagnostics.log_info(f"{key} - success")
    else:
      diagnostics.log_err(f"{key} - failed")

  return

if __name__ == "__main__":
  run()