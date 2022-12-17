import os
import argparse

def run(clean):
  args = ""
  if clean:
    args += " -clean"

  os.system(f"py build/scripts/test.py {args}")

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("-clean", help="clean run, as if run for the first time", action="store_true")
  args,unknown = parser.parse_known_args()
  
  run(args.clean)