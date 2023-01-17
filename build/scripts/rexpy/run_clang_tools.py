# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: run_clang_tools.py
# Copyright (c) Nick De Breuck 2023
#
# ============================================

import os
import argparse
import subprocess
import rexpy.diagnostics
import rexpy.util
import rexpy.required_tools
import rexpy.diagnostics

def __run_command(command):
  proc = subprocess.Popen(command)
  streamdata = proc.communicate()[0]
  return proc.returncode

def run(projectName, compdb):
  script_path = os.path.dirname(__file__)
  root_path =  rexpy.util.find_root()

  clang_tidy_path = rexpy.required_tools.tool_paths_dict["clang_tidy_path"]
  clang_format_path = rexpy.required_tools.tool_paths_dict["clang_format_path"]
  clang_apply_replacements_path = rexpy.required_tools.tool_paths_dict["clang_apply_replacements_path"]

  rexpy.diagnostics.log_info("Running clang-tidy - auto fixes")
  rc = __run_command(f"py {script_path}/run_clang_tidy.py -clang-tidy-binary={clang_tidy_path} -clang-apply-replacements-binary={clang_apply_replacements_path} -config-file={root_path}/source/.clang-tidy_first_pass -p={compdb} -header-filter=.* -quiet") # force clang compiler, as clang-tools expect it

  if rc != 0:
    raise Exception("clang-tidy auto fixes failed")

  rexpy.diagnostics.log_info("Running clang-format")
  rc = __run_command(f"py {script_path}/run_clang_format.py --clang-format-executable={clang_format_path} -r -i {root_path}/source/{projectName}")

  if rc != 0:
    raise Exception("clang-format failed")

if __name__ == "__main__":
  # arguments setups
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-p", "--project", help="project name")
  parser.add_argument("-compdb", help="compiler database folder")
  args, unknown = parser.parse_known_args()

 # useful for debugging
  rexpy.diagnostics.log_info(f"Executing {__file__}")

 # execute the script
  run(args.project, args.compdb)

 # print. We're done.
  rexpy.diagnostics.log_info("Done.")

  exit(0)