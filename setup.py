# ============================================ 
#
# Author: Nick De Breuck
# Twitter: @nick_debreuck
# 
# File: setup.py
# Copyright (c) Nick De Breuck 2023
#
# ============================================

# this is the only file that can't use rexpy.
# as this will install rexpy if it's not yet installed.

import os
import argparse
import pkg_resources
import shutil

def is_rexpy_installed():
  installed = {pkg.key for pkg in pkg_resources.working_set}
  if "rexpy" in installed:
    return True

  return False

def install_rexpy(forceInstall, installDir):
  # first set our working directory to rexpy.
  # this way the package will be installed in {root}/build/scripts/rexpy
  # this keeps the root clean.

  # first let's make sure we're in the root directory
  # we don't have access to rexpy yet, we'll have to manually
  # check if we're in the root.

  # let's assume if "build", "source" and "tests" are found, we're in the root
  build_exists = os.path.exists("./build")
  source_exists = os.path.exists("./source")
  tests_exists = os.path.exists("./tests")

  if not build_exists or not source_exists or not tests_exists:
    print("Error: You're not running setup.py from the root directory. Please run this from the root directory and try again")

  if forceInstall == False and is_rexpy_installed():
    print(f"rexpy is already installed - skipping install")
    return

  # rexpy is located in build/scripts/rexpy
  cwd = os.getcwd()
  new_wd = os.path.join(cwd, "build", "scripts", "rexpy")
  os.chdir(new_wd)

  # now run the install script.
  cmd = f"py {os.path.join(new_wd, 'install.py')} install"
  if installDir != "":
    cmd += f" -install-lib={installDir}"
  print(f"Trying to install rexpy by running: {cmd}")
  res = os.system(f"py {os.path.join(new_wd, 'install.py')} install")

  if res != 0:
    raise Exception("Failed to install RexPy")

  # this will result in a few new folders generated, which we can safely remove
  # these folders are "build", "dist" and "rexpy.egg-info"
  shutil.rmtree("build")
  shutil.rmtree("dist")
  shutil.rmtree("rexpy.egg-info")

  # reset the working directory
  os.chdir(cwd)

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("-update_rexpy", help="update rexpy, this is basically a reinstall", action="store_true")
  parser.add_argument("-install_dir", help="the install directory where rexpy will be installed", default="")

  args, unknown = parser.parse_known_args()

  install_rexpy(args.update_rexpy, args.install_dir)

  # now that rexpy is installed, we can safely call the rest of the code

  arguments_to_pass_on = ""
  for arg in unknown:
    arguments_to_pass_on += f" {arg}"

  os.system(f"py build/scripts/rexpy/rexpy/setup.py{arguments_to_pass_on}")