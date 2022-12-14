import os
import termcolor
from colorama import Fore, Back, Style

def run():
  os.system(f"py build/scripts/clean.py -root=.")

if __name__ == "__main__":
  # if __import__("platform").system() == "Windows":
  kernel32 = __import__("ctypes").windll.kernel32
  kernel32.SetConsoleMode(kernel32.GetStdHandle(-11), 7)
  del kernel32

  print(Fore.RED + "some red text")

  run()