import os
import argparse
import rexpy.util
import rexpy.rex_json
import rexpy.required_tools
import rexpy.required_libs
import shutil

root_path = rexpy.util.find_root()
settings = rexpy.rex_json.load_file(os.path.join(root_path, "build", "config", "settings.json"))
intermediate_dir = os.path.join(rexpy.util.find_root(), settings["intermediate_folder"])

def __clean_intermediate():
  # this clean the entire intermediate directory and all sub folders
  if os.path.exists(intermediate_dir):
    shutil.rmtree(intermediate_dir)

def run(shouldClean):
  if shouldClean:
    __clean_intermediate()
      
  rexpy.required_tools.run()
  rexpy.required_libs.run()
      
if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("-clean", help="clean setup, as if run for the first time", action="store_true")
  args, unknown = parser.parse_known_args()

  run(args.clean)