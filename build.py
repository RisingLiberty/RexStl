import os
import argparse

from pathlib import Path

def run(clean):
  args = ""

  if clean:
    args += " -clean"

  files = os.listdir(os.getcwd())
  for file in files:
    if Path(file).suffix == ".ninja":
      os.system(f"py build/scripts/build.py -ninja_file={file} {args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  
  parser.add_argument("-clean", help="clean all intermediate files first", action="store_true")
  args, unknown = parser.parse_known_args()

  run(parser.clean)