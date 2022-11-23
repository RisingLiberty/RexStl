import shutil
import os

import input

def run():
  response = input.ask("Tools are now downloaded.\nWould you like to copy these to a user directory so they're not in this repository? (Y/N)")
  if input.affirmative_response(response):
    response = input.ask("Please enter the path where you'd like to store them")
    __relocate_tools(response)

def __relocate_tools(dest):
  print("Copying files..")
  shutil.copytree("_build/tools", os.path.join(dest, "tools"))
  print("Copying files - Done")