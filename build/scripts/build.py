import os
import rex_json
import util
import required_tools
from pathlib import Path
import argparse
import diagnostics

tool_paths = required_tools.tool_paths

def run(ninjaFile, clean): 

  ninja_path = tool_paths["ninja_path"]
  if clean:
    os.system(f"{ninja_path} -f {ninjaFile} -t clean")

  os.system(f"{ninja_path} -f {ninjaFile}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-ninja_file", help="ninja file to build")
  parser.add_argument("-clean", help="clean all intermediate files first", action="store_true")
  args, unknown = parser.parse_known_args()
  
  run(args.ninja_file, run.clean)