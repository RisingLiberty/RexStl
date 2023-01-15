import os
import rex_json
import util
import required_tools
from pathlib import Path
import argparse
import shutil
import diagnostics

tool_paths_dict = required_tools.tool_paths_dict
root_path = util.find_root()
settings = rex_json.load_file(os.path.join(root_path, "build", "config", "settings.json"))

def run():
  intermediate_build_path = os.path.join(root_path, settings["intermediate_directory"], settings["build_folder"])
  intermediate_tests_path = os.path.join(root_path, settings["intermediate_directory"], settings["tests_folder"])
  intermediate_ninja_path = os.path.join(root_path, ".ninja")

  if os.path.exists(intermediate_build_path):
    shutil.rmtree(intermediate_build_path)
  if os.path.exists(intermediate_tests_path):
    shutil.rmtree(intermediate_tests_path)
  if os.path.exists(intermediate_ninja_path):
    shutil.rmtree(intermediate_ninja_path)

  vs_files = util.find_files_with_extension(root_path, ".sln")
  for vs_file in vs_files:
    os.remove(vs_file)
  ninja_files = util.find_files_with_extension(root_path, ".ninja")
  for ninja_file in ninja_files:
    os.remove(ninja_file)

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  run()
