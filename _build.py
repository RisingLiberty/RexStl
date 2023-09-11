# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: build.py
# Copyright (c) Nick De Breuck 2023
#
# ============================================

import sys
import argparse
import regis.build
import regis.util
import regis.diagnostics
import regis.task_raii_printing
import regis.dir_watcher

from pathlib import Path

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  
  parser.add_argument("-clean", help="clean all intermediate files first", action="store_true")
  parser.add_argument("-project", default="rexstdexe", help="project to build")
  parser.add_argument("-config", default="debug_opt", help="configuration to build for")
  parser.add_argument("-compiler", default="unknown", help="configuration to build with")

  args, unknown = parser.parse_known_args()

  if args.compiler == "unknown":
    if regis.util.is_windows():
      args.compiler = "msvc"
    else:
      args.compiler = "clang"

  intermediate_dir = ""

  task = regis.task_raii_printing.TaskRaiiPrint("Building")

  with regis.dir_watcher.DirWatcher('.', True) as dir_watcher:
    result = regis.build.new_build(args.project, args.config, args.compiler, intermediate_dir, args.clean)

  if result != 0:
    regis.diagnostics.log_err("Build failed")
    sys.exit(result)
  else:
    output = dir_watcher.filter_created_or_modified_files(lambda dir: dir.endswith('.exe') or dir.endswith('.lib'))

    regis.diagnostics.log_info("Build successful")  
    regis.diagnostics.log_info('--- Output --- ')
    for output_file in output:
      regis.diagnostics.log_info(output_file)
