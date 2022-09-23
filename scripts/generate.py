# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: generate.py
# Copyright (c) Nick De Breuck 2022
#
# ============================================

# This file should do the following:
# 1) generate a compiler database.
# 2) generate a shadow build (Visual Studio by default)

import argparse
import os
import time

import diagnostics

def run(cmakeArgs : str):
  logger.info("Generating Ninja")
  result = os.system("cmake -G Ninja -B .rex/build/ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON")
  if result != 0:
    logger.error("Failed to generate ninja, possible cmake errors")
    input()
    logger.critical("Ninja generation failure)")
  
  logger.info("CMake call")
  os.system(f"cmake {cmakeArgs}")

if __name__ == "__main__":
  # arguments setups
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-l", "--level", default="info", help="logging level")
  parser.add_argument("-cmake", help="commands to be passed to cmake")
  
  args, unknown = parser.parse_known_args()
  
 # initialize the logger
  log_level_str = args.level
  log_level = diagnostics.logging_level_from_string(log_level_str)
  logger = diagnostics.StreamLogger("setup", log_level)

 # useful for debugging
  logger.info(f"Executing {__file__}")

  if args.cmake == None:
    logger.critical("No cmake arguments provided")

 # execute the script
  run(args.cmake)

 # print. We're done.
  logger.info("Done.")