import os
import rexpy.required_tools

tool_paths_dict = rexpy.required_tools.tool_paths_dict
def new_build(ninjaFile, shouldClean):
  ninja_path = tool_paths_dict["ninja_path"]
  if shouldClean:
    os.system(f"{ninja_path} -f {ninjaFile} -t clean")

  os.system(f"{ninja_path} -f {ninjaFile}")