# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: required_libs.py
# Copyright (c) Nick De Breuck 2022
#
# ============================================

# This script is specifically designed to all required libraries for Rex.

import os
import rexpy.task_raii_printing
import rexpy.util
import rexpy.rex_json
import rexpy.diagnostics
import threading
import requests
import zipfile 
import shutil
from pathlib import Path

root = rexpy.util.find_root()
settings = rexpy.rex_json.load_file(os.path.join(root, "build", "config", "settings.json"))
build_dir = os.path.join(root, settings["build_folder"])
temp_dir = os.path.join(root, settings["intermediate_folder"])
tools_install_dir = os.path.join(temp_dir, settings["tools_folder"])
libs_install_dir = os.path.join(temp_dir, settings["libs_folder"])
lib_paths_filepath = os.path.join(libs_install_dir, "lib_paths.json")
zip_downloads_path = os.path.join(libs_install_dir, "zips")

lib_paths_dict = {}
if os.path.exists(lib_paths_filepath):
  lib_paths_dict = rexpy.rex_json.load_file(lib_paths_filepath)
required_libs = []
not_found_libs = []

def __load_required_libs_dict():
  libs_required = []
  json_blob = rexpy.rex_json.load_file(os.path.join(root, "build", "config", "required_libs.json"))
  for object in json_blob:
    libs_required.append(json_blob[object])

  return libs_required

def __print_lib_found(lib_path, path : str):
  rexpy.diagnostics.log_info(f"{lib_path} found at {path}")

# finds any of the paths in the required lib and checks if they're cached already
# if they're not it adds them to a local list and returns that list
def __find_uncached_paths(lib):
  config_name = lib["config_name"]
  required_lib_paths = lib["paths"]
  cached_lib_paths = []
  if config_name in lib_paths_dict:
    cached_lib_paths = lib_paths_dict[config_name]
  
  lib_paths_to_search = []
  for lib_path in required_lib_paths:
    # first let's check if the path is already in the cached paths
    # if it's not in there, then we have to look for it later
    abs_path = rexpy.util.find_directory_in_paths(lib_path, cached_lib_paths)

    if abs_path == None:
      lib_paths_to_search.append(lib_path)
      continue

    # if it is there, check if exists, if not, we'll have to look for it later as well
    if not os.path.exists(abs_path):
      rexpy.diagnostics.log_warn(f"lib path cached but doesn't exist: {lib_path}")
      lib_paths_to_search.append(lib_path)
      continue

    # otherwise print that we've found the path
    __print_lib_found(lib_path, abs_path)
    
  return lib_paths_to_search

def __look_for_paths(lib, pathsToSearch : list[str], whereToSearch : list[str]):
  not_found_paths = []
  for path in pathsToSearch:
    abs_path = rexpy.util.find_directory_in_paths(path, whereToSearch)
    if abs_path == None:
      not_found_paths.append(path)
      continue

    __print_lib_found(path, abs_path)
    config_name = lib["config_name"]
    if config_name not in lib_paths_dict:
      lib_paths_dict[config_name] = [] 
    lib_paths_dict[config_name].append(abs_path)

  return not_found_paths

def __download_file(url):
  filename = os.path.basename(url)
  filepath = os.path.join(zip_downloads_path, filename)
  
  if not os.path.exists(filepath):
    response = requests.get(url)
    open(filepath, "wb").write(response.content)

def __launch_download_thread(url):
    thread = threading.Thread(target=__download_file, args=(url,))
    thread.start()
    return thread  

def __download_lib(name, numZipFiles):
  task_print = rexpy.task_raii_printing.TaskRaiiPrint(f"Downloading lib {name}")

  threads = []
  for i in range(numZipFiles):
    threads.append(__launch_download_thread((f"https://github.com/RisingLiberty/RegisZip/raw/main/data/{name}.zip.{(i + 1):03d}")))

  for thread in threads:
    thread.join()

def __enumerate_libs(zipsFolder):
  zips = os.listdir(zipsFolder)
  libs = []
  for zip in zips:
    stem = Path(zip).stem
    if stem not in libs:
      libs.append(stem)

  return libs

def __enumerate_zip_files_for_lib(stem, folder):
  zips = os.listdir(folder)
  lib_zip_files = []
  for zip in zips:
    if Path(zip).stem == stem:
      lib_zip_files.append(os.path.join(folder, zip))

  return lib_zip_files

def __unzip_lib(name):
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("Unzipping files")
  libs_to_unzip = __enumerate_libs(zip_downloads_path)

  for lib in libs_to_unzip:
    lib_zip_files = __enumerate_zip_files_for_lib(lib, zip_downloads_path)
    lib_master_zip = os.path.join(zip_downloads_path, f"{lib}.zip")
    with open(lib_master_zip, "ab") as f:
      for lib_zip in lib_zip_files:
        with open(lib_zip, "rb") as z:
            f.write(z.read())

    with zipfile.ZipFile(lib_master_zip, "r") as zip_obj:
        zip_obj.extractall(libs_install_dir)

  rexpy.diagnostics.log_info(f"libs unzipped to {libs_install_dir}")

def __look_for_required_libs(required_libs):
  not_found_libs = []
  install_paths = rexpy.util.env_paths()
  install_paths.append(tools_install_dir)
  install_paths.append(libs_install_dir)
  for required_lib in required_libs:
    uncached_paths = __find_uncached_paths(required_lib)
    paths_not_found = __look_for_paths(required_lib, uncached_paths, install_paths)
    
    if len(paths_not_found) > 0:
      rexpy.diagnostics.log_warn("Couldn't find some paths")
      
      for path in paths_not_found:
        rexpy.diagnostics.log_warn(path)
      
      not_found_libs.append(required_lib)
            
  return not_found_libs

# checks all paths of the required libs, making sure all of them are installed
# if they're not installed, it'll flag a required_lib as not fully installed
def are_installed():
  task_print = rexpy.task_raii_printing.TaskRaiiPrint("Checking if libs are installed")

  global required_libs
  required_libs = __load_required_libs_dict()
  
  global lib_paths_dict
  if lib_paths_dict == None:
    lib_paths_dict = {}
    
  global not_found_libs
  not_found_libs = __look_for_required_libs(required_libs)
  
  return len(not_found_libs) == 0

def download():
  # create the temporary path for zips
  if not os.path.exists(zip_downloads_path):
      os.makedirs(zip_downloads_path)

  # filter duplicate tools
  libs_to_download = []
  for not_found_tool in not_found_libs:
    archive_name = not_found_tool["archive_name"]
    should_add = True
    for tool_to_download in libs_to_download:
      if archive_name == tool_to_download["archive_name"]:
        should_add = False
        break
    
    if should_add:
      libs_to_download.append(not_found_tool)

  for lib in libs_to_download:
    __download_lib(lib["archive_name"], lib["num_zip_files"])
    __unzip_lib(lib)

  # remove it after all libs have been downloaded
  shutil.rmtree(zip_downloads_path)
  
def install():
  for lib in not_found_libs:
    config_name = lib["config_name"]
    if config_name in lib_paths_dict:
      lib_paths_dict[config_name].clear()
    paths_not_found = __look_for_paths(lib, lib["paths"], [libs_install_dir])
  
    if len(paths_not_found) > 0:
      rexpy.diagnostics.log_err(f"failed to install {config_name}")
  
def run():
  if not are_installed():
    download()
    install()

  rexpy.rex_json.save_file(lib_paths_filepath, lib_paths_dict)
  
if __name__ == "__main__":
  run()