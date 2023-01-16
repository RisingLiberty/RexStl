import os
import rexpy.diagnostics
import rexpy.rex_json
import rexpy.util
import required_tools
import argparse
import rexpy.diagnostics

root = rexpy.util.find_root()
settings = rexpy.rex_json.load_file(os.path.join(root, "build", "config", "settings.json"))
temp_dir = os.path.join(root, settings["intermediate_folder"])
tools_install_dir = os.path.join(temp_dir, settings["tools_folder"])
tool_paths_filepath = os.path.join(tools_install_dir, "tool_paths.json")
tool_paths_dict = rexpy.rex_json.load_file(tool_paths_filepath)

def new_generation(sharpmakeFiles : list[str], sharpmakeArgs : list[str]):
  sharpmake_path = tool_paths_dict["sharpmake_path"]
  if len(sharpmake_path) == 0:
    rexpy.diagnostics.log_err("Failed to find sharpmake path")
    return

  sharpmake_sources = ""
  for sharpmake_file in sharpmakeFiles:
    sharpmake_sources += "\""
    sharpmake_sources += sharpmake_file
    sharpmake_sources += "\", "

  sharpmake_sources = sharpmake_sources[0:len(sharpmake_sources) - 2]
  sharpmake_sources = sharpmake_sources.replace('\\', '/')

  os.system(f"{sharpmake_path} /sources({sharpmake_sources}) /diagnostics {sharpmakeArgs}")

# root = util.find_root()
# tool_paths_dict = required_tools.tool_paths_dict

# def run(sharpmakeMain, sharpmakeArguments, lightMode):
#   sharpmake_path = tool_paths_dict["sharpmake_path"]
  
#   if len(sharpmake_path) == 0:
#     raise Exception("Failed to find sharpmake path")
  
  
  
#   os.system(f"{sharpmake_path} /sources('{sharpmake_main}') /diagnostics {sharpmake_args}")

#   sharpmake_main = sharpmakeMain.replace('\\', '/')

#   sharpmake_args : str = ""
#   if sharpmakeArguments != None:
#     sharpmake_args = sharpmakeArguments

#   if lightMode:
#     sharpmake_args += " /vsOnly"

#   os.system(f"{sharpmake_path} /sources('{sharpmake_main}') /diagnostics {sharpmake_args}")

# if __name__ == "__main__":
#   parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

#   parser.add_argument("-sharpmake_main", help="sharpmake main path")
#   parser.add_argument("-sharpmake_args", help="additional arguments to pass to sharpmake")
#   parser.add_argument("-light", help="run in light mode", action="store_true")
#   args, unknown = parser.parse_known_args()

#   run(args.sharpmake_main, args.sharpmake_args, args.light)