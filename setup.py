import os
import argparse

def run(lightMode, clean):
  args = ""
  if lightMode:
    args += " -light"

  if clean:
    args += " -clean"

  os.system(f"py build/scripts/setup.py {args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument("-light", help="run in light mode", action="store_true")
  parser.add_argument("-clean", help="clean setup, as if run for the first time", action="store_true")

  args, unknown = parser.parse_known_args()

  run(args.light, args.clean)