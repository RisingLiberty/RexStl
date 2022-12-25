import os
import copy
import rex_json
import util
import task_raii_printing
import requests
import zipfile 
import shutil
import threading
import diagnostics
import argparse

from pathlib import Path

root = util.find_root()
build_dir = os.path.join(root, "build")
temp_dir = os.path.join(root, ".rex")
tools_install_dir = os.path.join(temp_dir, "tools")
config_dir = os.path.join(root, "build")
tool_paths_filepath = os.path.join(tools_install_dir, "paths.json")
tool_paths_dict = {}
if os.path.exists(tool_paths_filepath):
  tool_paths_dict = rex_json.load_file(tool_paths_filepath)
zip_downloads_path = os.path.join(tools_install_dir, "zips")
required_tools = []
not_found_tools = []

def __load_tool_requirements():
  tools_required = []
  json_blob = rex_json.load_file(os.path.join(root, "build", "config", "required_tools.json"))
  for object in json_blob:
    tools_required.append(json_blob[object])

  return tools_required

def __print_tool_found(tool, path : str):
  diagnostics.log_info(f"{tool['config_name']} found at {path}")

def are_installed():
  task_print = task_raii_printing.TaskRaiiPrint("Checking if tools are installed")

  global required_tools
  required_tools = __load_tool_requirements()
  
  global tool_paths_dict
  if tool_paths_dict == None:
    tool_paths_dict = {}
    
  global not_found_tools

  paths = util.env_paths()
  for required_tool in required_tools:
    stem = required_tool["stem"]
    config_name = required_tool["config_name"]

    # check if the tool path is already in the cached paths
    if config_name in tool_paths_dict:
      tool_path = tool_paths_dict[config_name]
      if (os.path.exists(tool_path)):
        __print_tool_found(required_tool, tool_path)
        continue
      else:
        diagnostics.log_err(f"Error: tool path cached, but path doesn't exist: {tool_path}")

    # if not, add the path of the tool directory where it'd be downloaded to
    paths_to_use = copy.deepcopy(paths)
    paths_to_use.append(os.path.join(tools_install_dir, required_tool["path"]))

    # look for the tool
    exe_extension = "" 
    if "extension" in required_tool:
      exe_extension = required_tool["extension"]
    elif util.is_windows():
      exe_extension = ".exe"

    absPath = util.find_file_in_paths(f"{stem}{exe_extension}", paths_to_use)

    # tool is found, add it to the cached paths
    if absPath != '':
      __print_tool_found(required_tool, absPath)
      tool_config_name = required_tool["config_name"]
      tool_paths_dict[tool_config_name] = absPath

    # tool is not found, add it to the list to be looked for later
    else:
      not_found_tools.append(required_tool)

  if len(not_found_tools) == 0:
    diagnostics.log_info("All tools found")
    rex_json.save_file(tool_paths_filepath, tool_paths_dict)
    return True
  else:
    diagnostics.log_warn(f"Tools that weren't found: ")
    for tool in not_found_tools:
      diagnostics.log_warn(f"\t-{tool['stem']}")

    return False

def __download_file(url):
  filename = os.path.basename(url)
  filePath = os.path.join(zip_downloads_path, filename)
  
  if not os.path.exists(filePath):
    response = requests.get(url)
    open(filePath, "wb").write(response.content)
  
def __make_zip_download_path():
  if not os.path.exists(zip_downloads_path):
    os.makedirs(zip_downloads_path)

def __download_tool(name, numZipFiles):
  task_print = task_raii_printing.TaskRaiiPrint(f"Downloading tool {name}")

  threads = []
  for i in range(numZipFiles):
    threads.append(__launch_download_thread((f"https://github.com/RisingLiberty/RegisZip/raw/main/data/{name}.zip.{(i + 1):03d}")))

  for thread in threads:
    thread.join()

def __download_tools_archive():
  task_print = task_raii_printing.TaskRaiiPrint("Downloading tools")

  # filter duplicate tools
  tools_to_download = []
  for not_found_tool in not_found_tools:
    archive_name = not_found_tool["archive_name"]
    should_add = True
    for tool_to_download in tools_to_download:
      if archive_name == tool_to_download["archive_name"]:
        should_add = False
        break
    
    if should_add:
      tools_to_download.append(not_found_tool)

  for not_found_tool in tools_to_download:
    arch_name = not_found_tool["archive_name"]
    num_zip_files = not_found_tool["num_zip_files"]
    __download_tool(arch_name, num_zip_files)
    
def __enumerate_tools(zipsFolder):
  zips = os.listdir(zipsFolder)
  tools = []
  for zip in zips:
    stem = Path(zip).stem
    if stem not in tools:
      tools.append(stem)

  return tools

def __zip_files_for_tool(stem, folder):
  zips = os.listdir(folder)
  tool_zip_files = []
  for zip in zips:
    if Path(zip).stem == stem:
      tool_zip_files.append(os.path.join(folder, zip))

  return tool_zip_files

def __unzip_tools():
  task_print = task_raii_printing.TaskRaiiPrint("Unzipping files")
  tools_to_unzip = __enumerate_tools(zip_downloads_path)

  for tool in tools_to_unzip:
    tool_zip_files = __zip_files_for_tool(tool, zip_downloads_path)
    tool_master_zip = os.path.join(zip_downloads_path, f"{tool}.zip")
    with open(tool_master_zip, "ab") as f:
      for tool_zip in tool_zip_files:
        with open(tool_zip, "rb") as z:
            f.write(z.read())

    with zipfile.ZipFile(tool_master_zip, "r") as zip_obj:
        zip_obj.extractall(tools_install_dir)

  diagnostics.log_info(f"tools unzipped to {tools_install_dir}")

def __delete_tmp_folders():
  shutil.rmtree(zip_downloads_path)

def __launch_download_thread(url):
    thread = threading.Thread(target=__download_file, args=(url,))
    thread.start()
    return thread  

def download():
  task_print = task_raii_printing.TaskRaiiPrint("Downloading tools")
  __make_zip_download_path()
  __download_tools_archive()
  __unzip_tools()
  __delete_tmp_folders()

def install():
  task_print = task_raii_printing.TaskRaiiPrint("installing tools")

  global tool_paths_dict
  global not_found_tools
  for tool in not_found_tools:

    # look for tool in the folder where it'd be downloaded to
    exe_extension = "" 
    if "extension" in tool:
      exe_extension = tool["extension"]
    elif util.is_windows():
      exe_extension = ".exe"

    path = util.find_file_in_folder(f"{tool['stem']}{exe_extension}", os.path.join(tools_install_dir, tool["path"]))

    # if not found, something is wrong and we have to investigate manually
    if path == '':
      tool_name = tool["stem"]
      diagnostics.log_err(f"failed to find {tool_name}")
    else:
      # if found, add it to the cached paths
      __print_tool_found(tool, path)
      tool_config_name = tool["config_name"]
      tool_paths_dict[tool_config_name] = path
  
  # save cached paths to disk
  rex_json.save_file(tool_paths_filepath, tool_paths_dict)

if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument("-light", help="run in light mode", action="store_true")
  args, unknown = parser.parse_known_args()

  if not are_installed():
    if not args.light:
      download()
      install()
    else:
      diagnostics.log_info("Some tools weren't found, but setup is in light mode, no tools will get downloaded")

