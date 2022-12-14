import os
import argparse

def run(generateUnitTests):

  sharpmakeArgs = ""
  if generateUnitTests != None:
    sharpmakeArgs = "/generateTests"
  os.system(f"py build/scripts/generate.py -sharpmake_main=build/sharpmake/src/main.sharpmake.cs -sharpmake_args={sharpmakeArgs}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-generate_unittests", help="generate unit tests")

  args, unknown = parser.parse_known_args()

  run(args.generate_unittests)