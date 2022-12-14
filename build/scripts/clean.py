import os
import rex_json
import util
import required_tools
from pathlib import Path
import argparse
import diagnostics

tool_paths = required_tools.tool_paths

def run(rootDir):
  ninja_path = tool_paths["ninja_path"]

  ninja_files = util.find_files_with_extension(rootDir, ".ninja")
  for ninja_file in ninja_files:
    os.system(f"{ninja_path} -f {ninja_file} -t clean")

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("--root", help="root directory to look for ninja files")
  args, unknown = parser.parse_known_args()

  run(args.root)