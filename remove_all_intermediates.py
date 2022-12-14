import os

def run():
  os.system(f"py build/scripts/remove_all_intermediates.py")

if __name__ == "__main__":
  run()