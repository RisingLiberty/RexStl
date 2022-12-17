import os
import argparse

def run(generateUnitTests, lightMode):

  sharpmakeArgs = ""
  if generateUnitTests != None:
    sharpmakeArgs += " /generateTests"

  if lightMode:
    sharpmakeArgs += " /vsOnly"

  os.system(f"py build/scripts/generate.py -sharpmake_main=build/sharpmake/src/main.sharpmake.cs -sharpmake_args={sharpmakeArgs}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)

  parser.add_argument("-generate_unittests", help="generate unit tests")
  parser.add_argument("-light", help="run in light mode", action="store_true")

  args, unknown = parser.parse_known_args()

  run(args.generate_unittests, args.light)