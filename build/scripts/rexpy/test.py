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
import os
import traceback
import shutil
import time
import rexpy.required_tools
import rexpy.util
import rexpy.task_raii_printing
import rexpy.rex_json
import rexpy.code_coverage
import rexpy.diagnostics

from pathlib import Path
from datetime import datetime

root_path = rexpy.util.find_root()
tool_paths_dict = rexpy.required_tools.tool_paths_dict
settings = rexpy.rex_json.load_file(os.path.join(root_path, "build", "config", "settings.json"))
__pass_results = {}

def get_pass_results():
  return __pass_results

def __is_in_line(line : str, keywords : list[str]):
  for keyword in keywords:
    if keyword.lower() in line.lower():
      return True

  return False

def __default_output_callback(output):
  error_keywords = ["failed", "error"]
  warn_keywords = ["warning"]

  for line in iter(output.readline, b''):
    new_line : str = line.decode('UTF-8')
    if new_line.endswith('\n'):
      new_line = new_line.removesuffix('\n')

    if __is_in_line(new_line, error_keywords):
      rexpy.diagnostics.log_err(new_line)
      continue
    elif __is_in_line(new_line, warn_keywords):
      rexpy.diagnostics.log_warn(new_line)
      continue
    
    rexpy.diagnostics.log_no_color(new_line)

def __run_include_what_you_use(fixIncludes = False):
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running include-what-you-use")

  intermediate_folder = os.path.join(root_path, settings["intermediate_folder"], settings["build_folder"])
  result = rexpy.util.find_all_files_in_folder(intermediate_folder, "compile_commands.json")
    
  for compiler_db in result:
    iwyu_path = tool_paths_dict["include_what_you_use_path"]
    iwyu_tool_path = os.path.join(Path(iwyu_path).parent, "iwyu_tool.py")
    fix_includes_path = os.path.join(Path(iwyu_path).parent, "fix_includes.py")
    compiler_db_folder = Path(compiler_db).parent
    output_path = os.path.join(compiler_db_folder, "iwyu_output.log")
    os.system(f"py {iwyu_tool_path} -v -p={compiler_db_folder} > {output_path}") # needs to use os.system or iwyu will parse the command incorrectly
    if fixIncludes:
      os.system(f"py {fix_includes_path} --update_comments --safe_headers < {output_path}")
    
    rexpy.diagnostics.log_info(f"include what you use info saved to {output_path}")

  return 0

def __run_clang_tidy():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running clang-tidy")

  intermediate_folder = os.path.join(root_path, settings["intermediate_folder"], settings["build_folder"])
  result = rexpy.util.find_all_files_in_folder(intermediate_folder, "compile_commands.json")

  rc = 0
  for compiler_db in result:
    script_path = os.path.dirname(__file__)
    clang_tidy_path = tool_paths_dict["clang_tidy_path"]
    clang_apply_replacements_path = tool_paths_dict["clang_apply_replacements_path"]
    compiler_db_folder = Path(compiler_db).parent
    config_file_path = f"{root_path}/source/.clang-tidy_second_pass"

    cmd = f"py {script_path}/run_clang_tidy.py"
    cmd += f" -clang-tidy-binary={clang_tidy_path}"
    cmd += f" -clang-apply-replacements-binary={clang_apply_replacements_path}"
    cmd += f" -config-file={config_file_path}"
    cmd += f" -p={compiler_db_folder}"
    cmd += f" -header-filter=.*"
    cmd += f" -quiet"

    proc = rexpy.util.run_subprocess_with_callback(cmd, __default_output_callback)
    new_rc = rexpy.util.wait_for_process(proc)
    if new_rc != 0:
      rexpy.diagnostics.log_err(f"clang-tidy failed for {compiler_db}")
      rexpy.diagnostics.log_err(f"config file: {config_file_path}")
    rc |= new_rc

  return rc

def __generate_test_files(generateArgs):
  generate_script = os.path.join(root_path, "generate.py")
  proc = rexpy.util.run_subprocess(f"py {generate_script} {generateArgs}")
  return rexpy.util.wait_for_process(proc)

def __build_test_files(buildArgs):
  build_script = os.path.join(root_path, "build.py")
  proc = rexpy.util.run_subprocess(f"py {build_script} {buildArgs}")
  return rexpy.util.wait_for_process(proc)

def __find_test_programs(folder):
  intermediate_folder = os.path.join(folder)
  rexpy.diagnostics.log_info(f"looking for executables in {os.path.join(root_path, intermediate_folder)}")
  result = rexpy.util.find_all_files_in_folder(os.path.join(root_path, intermediate_folder), "*")
  coverage_programs = []
  for res in result:
    if rexpy.util.is_executable(res):
      coverage_programs.append(res.absolute())

  return coverage_programs

# unit tests
def __generate_tests():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("generating unit test projects")
  return __generate_test_files("-unittests")

def __build_tests():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("building tests")
  return __build_test_files(os.path.join(root_path, settings["intermediate_folder"], settings["tests_folder"], settings["build_folder"]), "*.ninja")

def __run_unit_tests():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running unit tests")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_folder"], settings["tests_folder"], settings["build_folder"]))
  
  rc = 0
  for program in unit_test_programs:
    rexpy.diagnostics.log_info(f"running: {Path(program).name}")
    proc = rexpy.util.run_subprocess(program)
    new_rc = rexpy.util.wait_for_process(proc)
    if new_rc != 0:
      rexpy.diagnostics.log_err(f"unit test failed for {program}") # use full path to avoid ambiguity
    rc |= new_rc

  return rc

# coverage
def __generate_coverage():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("generating coverage code")
  return __generate_test_files("-asan")

def __build_coverage():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("building coverage code")
  return __build_test_files(root_path, "*_coverage.ninja")

def __run_coverage():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running coverage")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_folder"], settings["coverage_folder"]))

  rc = 0
  for program in unit_test_programs:
    rexpy.diagnostics.log_info(f"running: {Path(program).name}")
    os.environ["LLVM_PROFILE_FILE"] = __get_coverage_rawdata_filename(program) # this is what llvm uses to set the raw data filename for the coverage data
    proc = rexpy.util.run_subprocess(program)
    new_rc = rexpy.util.wait_for_process(proc)
    if new_rc != 0:
      rexpy.diagnostics.log_err(f"unit test failed for {program}") # use full path to avoid ambiguity
    rc |= new_rc

  return unit_test_programs

def __relocate_coverage_data(programsRun : list[str]):
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("relocating coverage files")
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
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("indexing rawdata files")
  output_files = []

  for file in rawdataFiles:
    output_files.append(rexpy.code_coverage.create_index_rawdata(file))

  return output_files

def __create_coverage_reports(programsRun, indexdataFiles):
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("creating coverage reports")

  rc = 0
  for index in range(len(programsRun)):
    program = programsRun[index]
    indexdata_file = indexdataFiles[index]

    if Path(program).stem != Path(indexdata_file).stem:
      rc = 1
      rexpy.diagnostics.log_err(f"program stem doesn't match coverage file stem: {Path(program).stem} != {Path(indexdata_file).stem}")

    rexpy.code_coverage.create_line_oriented_report(program, indexdata_file)
    rexpy.code_coverage.create_file_level_summary(program, indexdata_file)
    rexpy.code_coverage.create_lcov_report(program, indexdata_file)

  return rc

def __parse_coverage_reports(indexdataFiles):
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("parsing coverage reports")

  rc = 0
  for indexdata_file in indexdataFiles:
    report_filename = rexpy.code_coverage.get_file_level_summary_filename(indexdata_file)
    rc |= rexpy.code_coverage.parse_file_summary(report_filename)

  return rc

def __get_coverage_rawdata_filename(program : str):
  return f"{Path(program).stem}.profraw"

# asan
def __generate_address_sanitizer():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("generating address sanitizer code")
  return __generate_test_files("-asan")

def __build_address_sanitizer():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("building address sanitizer code")
  return __build_test_files(root_path, "-asan")

def __run_address_sanitizer():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running address sanitizer tests")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_folder"], settings["tests_folder"], "asan"))
  
  rc = 0
  for program in unit_test_programs:
    rexpy.diagnostics.log_info(f"running: {Path(program).name}")
    log_folder_path = Path(program).parent
    log_folder = log_folder_path.as_posix()
    
    # for some reason, setting an absolute path for the log folder doesn't work
    # so we have to set the working directory of the program to where it's located so the log file will be there as well
    # ASAN_OPTIONS common flags: https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
    # ASAN_OPTIONS flags: https://github.com/google/sanitizers/wiki/AddressSanitizerFlags
    asan_options = f"print_stacktrace=1:log_path=asan.log"
    os.environ["ASAN_OPTIONS"] = asan_options # print callstacks and save to log file
    
    proc = rexpy.util.run_subprocess_with_working_dir(program, log_folder)
    new_rc = rexpy.util.wait_for_process(proc)
    log_file_path = os.path.join(log_folder, f"asan.log.{proc.pid}")
    if new_rc != 0 or os.path.exists(log_file_path):
      rexpy.diagnostics.log_err(f"address sanitizer failed for {program}") # use full path to avoid ambiguity
      rexpy.diagnostics.log_err(f"for more info, please check: {log_file_path}")
      new_rc = 1
    rc |= new_rc

  return rc

# ubsan
def __generate_undefined_behavior_sanitizer():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("generating undefined behavior sanitizer code")
  return __generate_test_files("-ubsan")

def __build_undefined_behavior_sanitizer():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("building undefined behavior sanitizer code")
  return __build_test_files(root_path, "-ubsan")

def __run_undefined_behavior_sanitizer():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running undefined behavior sanitizer tests")
  unit_test_programs = __find_test_programs(os.path.join(settings["intermediate_folder"], settings["tests_folder"], "ubsan"))
  
  rc = 0
  for program in unit_test_programs:
    rexpy.diagnostics.log_info(f"running: {Path(program).name}")
    log_folder_path = Path(program).parent
    log_folder = log_folder_path.as_posix()
    
    # for some reason, setting an absolute path for the log folder doesn't work
    # so we have to set the working directory of the program to where it's located so the log file will be there as well
    # UBSAN_OPTIONS common flags: https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
    ubsan_options = f"print_stacktrace=1:log_path=ubsan.log"
    os.environ["UBSAN_OPTIONS"] = ubsan_options # print callstacks and save to log file
    proc = rexpy.util.run_subprocess_with_working_dir(program, log_folder)
    new_rc = rexpy.util.wait_for_process(proc)
    log_file_path = os.path.join(log_folder, f"ubsan.log.{proc.pid}")
    if new_rc != 0 or os.path.exists(log_file_path): # if there's a ubsan.log.pid created, the tool found issues
      rexpy.diagnostics.log_err(f"undefined behavior sanitizer failed for {program}") # use full path to avoid ambiguity
      rexpy.diagnostics.log_err(f"for more info, please check: {log_file_path}")
      new_rc = 1
    rc |= new_rc

  return rc

# fuzzy
def __generate_fuzzy_testing():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("generating fuzzy testing code")
  return __generate_test_files("-fuzzy")

def __build_fuzzy_testing():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("building fuzzy testing code")
  return __build_test_files(root_path, "-fuzzy")

def __run_fuzzy_testing():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("running fuzzy tests")
  fuzzy_programs = __find_test_programs(os.path.join(settings["intermediate_folder"], settings["tests_folder"], "fuzzy"))
  
  rc = 0
  for program in fuzzy_programs:
    rexpy.diagnostics.log_info(f"running: {Path(program).name}")
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
    proc = rexpy.util.run_subprocess_with_working_dir(f"{program} -runs={num_runs}", log_folder)
    new_rc = rexpy.util.wait_for_process(proc)
    log_file_path = os.path.join(log_folder, f"fuzzy.log.{proc.pid}")
    if new_rc != 0 or os.path.exists(log_file_path): # if there's a ubsan.log.pid created, the tool found issues
      rexpy.diagnostics.log_err(f"fuzzy testing failed for {program}") # use full path to avoid ambiguity
      if os.path.exists(log_file_path):
        rexpy.diagnostics.log_err(f"issues found while fuzzing!")
        rexpy.diagnostics.log_err(f"for more info, please check: {log_file_path}")
      new_rc = 1
    rc |= new_rc

  return rc

def test_include_what_you_use():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __run_include_what_you_use()

  if rc != 0:
    rexpy.diagnostics.log_err(f"include-what-you-use pass failed")

  __pass_results["include-what-you-use"] = rc

def test_clang_tidy():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __run_clang_tidy() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"clang-tidy pass failed")

  __pass_results["clang-tidy"] = rc

def test_unit_tests():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_tests() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to generate tests")
  __pass_results["unit tests generation"] = rc

  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_tests() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to build tests")
  __pass_results["unit tests building"] = rc

  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_unit_tests() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"unit tests failed")
  __pass_results["unit tests result"] = rc

def test_code_coverage():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_coverage() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to generate coverage")
  __pass_results["coverage generation"] = rc

  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __build_coverage() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to build coverage")
  __pass_results["coverage building"] = rc

  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  programs_run = __run_coverage() # works
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rawdata_files = __relocate_coverage_data(programs_run) # works
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  indexdata_files = __index_rawdata_files(rawdata_files) # works
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __create_coverage_reports(programs_run, indexdata_files) # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to create coverage reports")
  __pass_results["coverage report creation"] = rc

  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __parse_coverage_reports(indexdata_files) # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"Not all the code was covered")
  __pass_results["coverage report result"] = rc

def test_asan():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_address_sanitizer() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to generate asan code")
  __pass_results["address sanitizer generation"] = rc

  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_address_sanitizer() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to build asan code")
  __pass_results["address sanitizer building"] = rc
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_address_sanitizer() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"invalid code found with asan")
  __pass_results["address sanitizer result"] = rc

def test_ubsan():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_undefined_behavior_sanitizer() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to generate ubsan code")
  __pass_results["undefined behavior sanitizer generation"] = rc
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_undefined_behavior_sanitizer() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to build ubsan code")
  __pass_results["undefined behavior sanitizer building"] = rc
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_undefined_behavior_sanitizer() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"invalid code found with ubsan")
  __pass_results["undefined behavior sanitizer result"] = rc

def test_fuzzy_testing():
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc = __generate_fuzzy_testing() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to generate fuzzy code")
  __pass_results["fuzzy testing generation"] = rc
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __build_fuzzy_testing() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"failed to build fuzzy code")
  __pass_results["fuzzy testing building"] = rc
  
  rexpy.diagnostics.log_no_color("-----------------------------------------------------------------------------")
  rc |= __run_fuzzy_testing() # works
  if rc != 0:
    rexpy.diagnostics.log_err(f"invalid code found with fuzzy")
  __pass_results["fuzzy testing result"] = rc

def __shutil_error(func, path, exec_info):
  rexpy.diagnostics.log_err(f"shutil error: {func}, {path}, {exec_info}")

def clean():
  intermediate_tests_path = os.path.join(root_path, settings["intermediate_folder"], settings["tests_folder"])
  if os.path.exists(intermediate_tests_path):
    shutil.rmtree(intermediate_tests_path, onerror=__shutil_error)
