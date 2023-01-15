import sys
import subprocess
import pkg_resources
import task_raii_printing
import diagnostics

def run():
  task_print = task_raii_printing.TaskRaiiPrint("Installing python modules")

  required = {'requests', 'termcolor'}
  installed = {pkg.key for pkg in pkg_resources.working_set}
  missing = required - installed

  if missing:
    for missingModule in missing:
      diagnostics.log_info(f"installing \"{missingModule}\"")

    python = sys.executable
    subprocess.check_call([python, '-m', 'pip', 'install', *missing], stdout=subprocess.DEVNULL)
