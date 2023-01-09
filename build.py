import os
import argparse

from pathlib import Path

def should_skip(file):
  if "_asan.ninja" in file:
    return True

  if "_coverage.ninja" in file:
    return True

  if "_fuzzy.ninja" in file:
    return True

  if "_ubsan.ninja" in file:
    return True

  return False

def run(clean):
  args = ""

  if clean:
    args += " -clean"

  files = os.listdir(os.getcwd())
  for file in files:
    if should_skip(file):
      continue

    if Path(file).suffix == ".ninja":
      os.system(f"py build/scripts/build.py -ninja_file={file} {args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  
  parser.add_argument("-clean", help="clean all intermediate files first", action="store_true")
  args, unknown = parser.parse_known_args()

  run(args.clean)