# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: run_clang_tools.py
# Copyright (c) Nick De Breuck 2022
#
# ============================================

import argparse
import os

import diagnostics

def run():
  root_path = os.path.dirname(__file__)
  logger.info("Running clang-tidy")
  os.system(f"py {root_path}/run_clang_tidy.py -p={root_path}/../.rex/build/ninja/ -header-filter=.* -format -quiet")
  logger.info("Running clang-format")
  os.system(f"py {root_path}/run_clang_format.py -r {root_path}/../source")

if __name__ == "__main__":
  # arguments setups
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-l", "--level", default="info", help="logging level")

  args, unknown = parser.parse_known_args()

 # initialize the logger
  log_level_str = args.level
  log_level = diagnostics.logging_level_from_string(log_level_str)
  logger = diagnostics.StreamLogger("setup", log_level)

 # useful for debugging
  logger.info(f"Executing {__file__}")

 # execute the script
  run()

 # print. We're done.
  logger.info("Done.")

  exit(0)