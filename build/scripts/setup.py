import install_modules
import os
import argparse
from pathlib import Path

def run(lightMode, shouldClean):
  install_modules.run()
  
  # can't call this directly in case some modules aren't installed
  script_folder = Path(__file__).parent
  args = ""
  if lightMode:
    args += " -light"

  if shouldClean:
    os.system(f"{os.path.join(script_folder, 'remove_all_intermediates.py')}")

  os.system(f"{os.path.join(script_folder, 'required_tools.py')} {args}")
  os.system(f"{os.path.join(script_folder, 'required_libs.py')} {args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument("-light", help="run in light mode", action="store_true")
  parser.add_argument("-clean", help="clean setup, as if run for the first time", action="store_true")
  args, unknown = parser.parse_known_args()

  run(args.light, args.clean)