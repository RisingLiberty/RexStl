import os
import task_raii_printing
import util
import rex_json
import diagnostics
import copy

root = util.find_root()
build_dir = os.path.join(root, "build")
temp_dir = os.path.join(root, ".rex")
libs_install_dir = os.path.join(temp_dir, "tools")
tools_install_dir = os.path.join(temp_dir, "tools")
lib_paths_filepath = os.path.join(tools_install_dir, "paths.json")
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

def are_installed():
  task_print = task_raii_printing.TaskRaiiPrint("Checking if libs are installed")

  global required_libs
  required_libs = __load_lib_requirements()
  
  global lib_paths_dict
  if lib_paths_dict == None:
    lib_paths_dict = {}
    
  global not_found_libs

  env_paths = util.env_paths()
  for required_lib in required_libs:
    required_lib_paths = required_lib["paths"]
    config_name = required_lib["config_name"]

    # check if the lib path is already in the cached paths
    if config_name in lib_paths_dict:
      lib_paths = lib_paths_dict[config_name]

      for lib_path in lib_paths:
        if (os.path.exists(lib_path)):
          __print_lib_found(required_lib, lib_path)
        else:
          diagnostics.log_err(f"Error: lib path cached, but path doesn't exist: {lib_path}")

      # if not, add the path of the lib directory where it'd be downloaded to
      paths_to_use = copy.deepcopy(env_paths)
      for required_lib_path in required_lib_paths:
        paths_to_use.append(os.path.join(libs_install_dir, required_lib_path))
        
      # look for the lib
      for required_lib_path in required_lib_paths:
        abs_path = util.find_directory_in_paths(required_lib_path, paths_to_use)
        if abs_path == None:
          not_found_libs.append(required_lib_path)
          continue

        __print_lib_found(required_lib, required_lib_path)
        lib_paths.append(abs_path)

  #   # lib is found, add it to the cached paths
  #   if absPath != '':
  #     __print_lib_found(required_lib, absPath)
  #     lib_config_name = required_lib["config_name"]
  #     lib_paths[lib_config_name] = absPath

  #   # lib is not found, add it to the list to be looked for later
  #   else:
  #     not_found_libs.append(required_lib)

  if len(not_found_libs) == 0:
    diagnostics.log_info("All libs found")
    rex_json.save_file(lib_paths_filepath, lib_paths)
    return True
  else:
    diagnostics.log_warn(f"Libs that weren't found: ")
    for lib in not_found_libs:
      diagnostics.log_warn(f"\t-{lib}")

    return False

if __name__ == "__main__":
  are_installed()
  # if not are_installed():
    # download()
    # install()