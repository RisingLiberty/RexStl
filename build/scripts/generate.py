import os
import rex_json
import util
import required_tools
import argparse
import diagnostics

root = util.find_root()
tool_paths = required_tools.tool_paths

def run(sharpmakeMain, sharpmakeArguments, lightMode):
  sharpmake_path = tool_paths["sharpmake_path"]
  
  if len(sharpmake_path) == 0:
    raise Exception("Failed to find sharpmake path")
  
  sharpmake_main = sharpmakeMain.replace('\\', '/')

  sharpmake_args : str = ""
  if sharpmakeArguments != None:
    sharpmake_args = sharpmakeArguments

  if lightMode:
    sharpmake_args += " /vsOnly"

  os.system(f"{sharpmake_path} /sources('{sharpmake_main}') /diagnostics {sharpmake_args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-sharpmake_main", help="sharpmake main path")
  parser.add_argument("-sharpmake_args", help="additional arguments to pass to sharpmake")
  parser.add_argument("-light", help="run in light mode", action="store_true")
  args, unknown = parser.parse_known_args()

  run(args.sharpmake_main, args.sharpmake_args, args.light)