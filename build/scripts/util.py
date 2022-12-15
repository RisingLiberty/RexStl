import os
import subprocess
from pathlib import Path
import diagnostics

def env_paths():
  envPath = os.environ["PATH"]
  paths = envPath.split(os.pathsep)
  return paths

def find_file_in_folder(file, path : str):
  fileToFind = file.lower()
  subFilesOrFolders = os.listdir(path)
  for fileOrFolder in subFilesOrFolders:
    absPath = os.path.join(path, fileOrFolder)
    if os.path.isfile(absPath):
      file_name = Path(absPath).name.lower()
      if file_name == fileToFind:
        return absPath
  
  return ''

def find_file_in_paths(file, directories : list[str]):
  for path in directories:
    if not os.path.exists(path):
      continue

    result = find_file_in_folder(file, path)
    if result != '':
      return result

  return ''

def find_directory_in_paths(dir : str, directories : list[str]):
  dir = dir.replace('\\', '/')
  folders = dir.split('/')  
  num_folders = len(folders)

  for path in directories:
    path = path.replace('\\', '/')
    path_folders = path.split('/')

    dir_idx = num_folders - 1
    path_idx = len(path_folders) - 1
    if (len(path_folders) < num_folders):
      continue

    while dir_idx >= 0:
      dir_folder = folders[dir_idx]
      path_folder = path_folders[path_idx]
      
      if dir_folder != path_folder:
        break

      dir_idx -= 1
      path_idx -= 1

    if dir_idx == -1:
      if os.path.exists(path):
        return path
      else:
        diagnostics.log_err(f"matching directory found, but doesn't exist: {path}")

  return None

def find_in_parent(path, toFind):
  curr_path = path

  while toFind not in os.listdir(curr_path):
    if Path(curr_path).parent == curr_path:
      diagnostics.log_err(f"{toFind} not found in parents of {path}")
      return ''

    curr_path = Path(curr_path).parent

  return curr_path

def find_root():
  res = find_in_parent(os.getcwd(), "build")
  if (res == ''):
    diagnostics.log_err(f"root not found")

  return res

def find_files_with_extension(path : str, extension : str):
  files = os.listdir(path)
  files_with_extension = []
  for file in files:
    if Path(file).suffix == extension:
      files_with_extension.append(file)

  return files_with_extension

def is_windows():
  return os.name == 'nt'

def run_subprocess(command):
  proc = subprocess.Popen(command)
  return proc

def run_subprocess_with_working_dir(command, workingDir):
  proc = subprocess.Popen(command, cwd=workingDir)
  return proc

def run_subprocess_with_callback(command, callback):
  proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  callback(proc.stdout)
  callback(proc.stderr)
  return proc

def wait_for_process(process):
  streamdata = process.communicate()[0]
  return process.returncode  

def is_executable(path):
  if is_windows():
    if Path(path).suffix == ".exe":
      return True
  else:
    return os.access(path, os.X_OK)

def find_all_files_in_folder(dir, toFindRegex):
  return list(Path(dir).rglob(toFindRegex))
