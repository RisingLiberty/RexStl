import os
import argparse

def run(lightMode):
  args = ""
  if lightMode:
    args += "-light"

  os.system(f"py build/scripts/setup.py {args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument("-light", help="run in light mode", action="store_true")
  args, unknown = parser.parse_known_args()

  run(args.light)