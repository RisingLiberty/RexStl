import rexpy.run_clang_tools
import rexpy.diagnostics
import argparse

def run(projectName, compdb):
  rexpy.run_clang_tools.run(projectName, compdb)
  return

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-p", "--project", help="project name")
  parser.add_argument("-comp", "--compiler", help="compiler")
  parser.add_argument("-conf", "--config", help="configuration")
  parser.add_argument("-compdb", help="compiler db folder")

  parser.add_argument("-l", "--level", default="info", help="logging level")
  args, unknown = parser.parse_known_args()

  project_name = args.project
  compiler = args.compiler
  config = args.config
  compdb = args.compdb

 # initialize the logger
  log_level_str = args.level
  log_level = rexpy.diagnostics.logging_level_from_string(log_level_str)
  logger = rexpy.diagnostics.StreamLogger("setup", log_level)

 # useful for debugging
  logger.info(f"Executing {__file__}")

 # execute the script
  run(project_name, compdb)

 # print. We're done.
  logger.info("Done.")

  exit(0)
