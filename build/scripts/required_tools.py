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
tool_paths = {}
if os.path.exists(tool_paths_filepath):
  tool_paths = rex_json.load_file(tool_paths_filepath)
zipDownloads = os.path.join(tools_install_dir, "zips")
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
  
  global tool_paths
  if tool_paths == None:
    tool_paths = {}
    
  global not_found_tools

  paths = util.env_paths()
  for required_tool in required_tools:
    stem = required_tool["stem"]
    config_name = required_tool["config_name"]

    # check if the tool path is already in the cached paths
    if config_name in tool_paths:
      tool_path = tool_paths[config_name]
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
    if util.is_windows():
      exe_extension = ".exe"

    absPath = util.find_file_in_paths(f"{stem}{exe_extension}", paths_to_use)

    # tool is found, add it to the cached paths
    if absPath != '':
      __print_tool_found(required_tool, absPath)
      tool_config_name = required_tool["config_name"]
      tool_paths[tool_config_name] = absPath

    # tool is not found, add it to the list to be looked for later
    else:
      not_found_tools.append(required_tool)

  if len(not_found_tools) == 0:
    diagnostics.log_info("All tools found")
    rex_json.save_file(tool_paths_filepath, tool_paths)
    return True
  else:
    diagnostics.log_warn(f"Tools that weren't found: ")
    for tool in not_found_tools:
      diagnostics.log_warn(f"\t-{tool['stem']}")

    return False

def __download_file(url):
  filename = os.path.basename(url)
  filePath = os.path.join(zipDownloads, filename)
  
  if not os.path.exists(filePath):
    response = requests.get(url)
    open(filePath, "wb").write(response.content)
  
def __make_zip_download_path():
  if not os.path.exists(zipDownloads):
    os.makedirs(zipDownloads)

def __download_tools_archive():
  task_print = task_raii_printing.TaskRaiiPrint("Downloading tools archive")

  threads = []

  # Yes I know we can download this using GitPython, but that's incredibly slow..
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.001")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.002")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.003")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.004")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.005")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.006")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.007")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.008")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.009")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.010")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.011")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.012")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.013")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.014")))
  threads.append(__launch_download_thread(("https://github.com/RisingLiberty/RegisZip/raw/main/data/Tools.zip.015")))

  for thread in threads:
    thread.join()

def __unzip_tools():
  task_print = task_raii_printing.TaskRaiiPrint("Unzipping files")

  zipPath = zipDownloads
  toolsZipFile = "tools.zip"
  zips = os.listdir(zipPath)
  for zipName in zips:
      with open(os.path.join(zipPath, toolsZipFile), "ab") as f:
          with open(os.path.join(zipPath, zipName), "rb") as z:
              f.write(z.read())

  with zipfile.ZipFile(os.path.join(zipPath, toolsZipFile), "r") as zipObj:
      zipObj.extractall(tools_install_dir)

  diagnostics.log_info(f"tools unzipped to {tools_install_dir}")

def __delete_tmp_folders():
  shutil.rmtree(zipDownloads)

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

  global tool_paths
  global not_found_tools
  for tool in not_found_tools:

    # look for tool in the folder where it'd be downloaded to
    exe_extension = "" 
    if util.is_windows():
      exe_extension = ".exe"

    diagnostics.log_info(f"looking for {tool['stem']}{exe_extension} in {os.path.join(tools_install_dir, tool['path'])}")
    path = util.find_file_in_folder(f"{tool['stem']}{exe_extension}", os.path.join(tools_install_dir, tool["path"]))

    # if not found, something is wrong and we have to investigate manually
    if path == '':
      tool_name = tool["stem"]
      diagnostics.log_err(f"failed to find {tool_name}")
    else:
      # if found, add it to the cached paths
      tool_config_name = tool["config_name"]
      tool_paths[tool_config_name] = path
  
  # save cached paths to disk
  rex_json.save_file(tool_paths_filepath, tool_paths)

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

