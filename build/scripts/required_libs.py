import os
import task_raii_printing
import util
import rex_json
import diagnostics
import copy
import argparse

root = util.find_root()
settings = rex_json.load_file(os.path.join(root, "build", "config", "settings.json"))
build_dir = os.path.join(root, settings["build_folder"])
temp_dir = os.path.join(root, settings["intermediate_directory"])
libs_install_dir = os.path.join(temp_dir, settings["tools_folder"])
tools_install_dir = os.path.join(temp_dir, settings["tools_folder"])
lib_paths_filepath = os.path.join(tools_install_dir, "lib_paths.json")
lib_paths_dict = {}
if os.path.exists(lib_paths_filepath):
  lib_paths_dict = rex_json.load_file(lib_paths_filepath)
required_libs = []
not_found_libs = []

def __load_lib_requirements():
  libs_required = []
  json_blob = rex_json.load_file(os.path.join(root, "build", "config", "required_libs.json"))
  for object in json_blob:
    libs_required.append(json_blob[object])

  return libs_required

def __print_lib_found(tool, path : str):
  diagnostics.log_info(f"{tool['config_name']} found at {path}")

def __find_paths_to_search(lib):
  config_name = lib["config_name"]
  required_lib_paths = lib["paths"]
  cached_lib_paths = []
  if config_name in lib_paths_dict:
    cached_lib_paths = lib_paths_dict[config_name]
  
  lib_paths_to_search = []
  for lib_path in required_lib_paths:
    # first let's check if the path is already in the cached paths
    # if it's not in there, then we have to look for it later
    abs_path = util.find_directory_in_paths(lib_path, cached_lib_paths)

    if abs_path == None:
      diagnostics.log_warn(f"will look for: {lib_path}")
      lib_paths_to_search.append(lib_path)
      continue

    # if it is there, check if exists, if not, we'll have to look for it later as well
    elif not os.path.exists(abs_path):
      diagnostics.log_warn(f"lib path cached but doesn't exist: {lib_path}")
      lib_paths_to_search.append(lib_path)
      continue

    # otherwise print that we've found the path
    __print_lib_found(lib, abs_path)
    
  return lib_paths_to_search

def __install_lib_paths(lib, pathsToSearch):
  paths_to_search = util.env_paths()
  for required_lib_path in pathsToSearch:
    paths_to_search.append(os.path.join(libs_install_dir, required_lib_path))

  not_found_paths = []
  for path in pathsToSearch:
    abs_path = util.find_directory_in_paths(path, paths_to_search)
    if abs_path == None:
      not_found_paths.append(path)
      continue

    __print_lib_found(lib, abs_path)
    config_name = lib["config_name"]
    if config_name not in lib_paths_dict:
      lib_paths_dict[config_name] = [] 
    lib_paths_dict[config_name].append(abs_path)

  return not_found_paths

def are_installed(lightMode):
  task_print = task_raii_printing.TaskRaiiPrint("Checking if libs are installed")

  global required_libs
  required_libs = __load_lib_requirements()
  
  global lib_paths_dict
  if lib_paths_dict == None:
    lib_paths_dict = {}
    
  all_libs_found = True
  global not_found_libs
  for required_lib in required_libs:
    paths_to_search = __find_paths_to_search(required_lib)
    paths_not_found = __install_lib_paths(required_lib, paths_to_search)
    
    for path in paths_not_found:
      diagnostics.log_err(f"{required_lib} path not found {path}")
      all_libs_found = False

  rex_json.save_file(lib_paths_filepath, lib_paths_dict)
  return all_libs_found

if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument("-light", help="run in light mode", action="store_true")
  args, unknown = parser.parse_known_args()

  are_installed(args.light)