import os
import rex_json
import util
import required_tools
from pathlib import Path
import argparse
import diagnostics

tool_paths_dict = required_tools.tool_paths_dict

def run(ninjaFile, clean): 

  ninja_path = tool_paths_dict["ninja_path"]
  if clean:
    os.system(f"{ninja_path} -f {ninjaFile} -t clean")

  os.system(f"{ninja_path} -f {ninjaFile}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-ninja_file", help="ninja file to build")
  parser.add_argument("-clean", help="clean all intermediate files first", action="store_true")
  args, unknown = parser.parse_known_args()
  
  run(args.ninja_file, args.clean)