import os
from pathlib import Path

def run():
  files = os.listdir(os.getcwd())
  for file in files:
    if Path(file).suffix == ".ninja":
      os.system(f"py build/scripts/build.py -ninja_file={file}")

if __name__ == "__main__":
  run()