import install_modules
import os
from pathlib import Path

def run():
  install_modules.run()
  
  # can't call this directly in case some modules aren't installed
  script_folder = Path(__file__).parent
  os.system(f"{os.path.join(script_folder, 'required_tools.py')}")

if __name__ == "__main__":
  run()