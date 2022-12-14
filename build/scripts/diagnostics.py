import logging
import termcolor

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    RESET = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Logger(object):
  def __init__(self, name = "logger", level = logging.DEBUG):
    if __import__("platform").system() == "Windows": # if running on Windows, enable console VT mode
      kernel32 = __import__("ctypes").windll.kernel32
      kernel32.SetConsoleMode(kernel32.GetStdHandle(-11), 7)
      del kernel32

    self.logger = logging.getLogger(name)
    self.logger.setLevel(level)

  def no_color(self, msg):
    print(msg)

  def debug(self, msg):
    termcolor.cprint(f"[debug] {msg}", "magenta")

  def info(self, msg):
    termcolor.cprint(f"[info] {msg}", "green")

  def warning(self, msg):
    termcolor.cprint(f"[warning] {msg}", "yellow")

  def error(self, msg):
    termcolor.cprint(f"[error] {msg}", "red")

  def critical(self, msg):
    self.logger.error(f"-- Critical Error Occurred --")
    self.logger.error(msg)
    raise Exception(msg)

class StreamLogger(Logger):
  def __init__(self, name = "logger", level = logging.DEBUG):
    super().__init__(name, level)

    sh = logging.StreamHandler()
    self.logger.addHandler(sh)

class FileLogger(Logger):
  def __init__(self, name = "logger", level = logging.DEBUG):
    super().__init__(name, level)

    fh = logging.FileHandler(f"{name}.log", "w")
    self.logger.addHandler(fh)

def logging_level_from_string(level):
  if level == "debug":
    return logging.DEBUG
  elif level == "info":
    return logging.INFO
  elif level == "warning":
    return logging.WARNING
  elif level == "error":
    return logging.ERROR
  elif level == "critical":
    return logging.CRITICAL

  return logging.NOTSET

__cout = StreamLogger("cout", logging.INFO)

def log_no_color(msg):
  __cout.no_color(f"{msg}")

def log_debug(msg):
  __cout.debug(f"{msg}")

def log_info(msg):
  __cout.info(f"{msg}")

def log_warn(msg):
  __cout.warning(f"{msg}")

def log_err(msg):
  __cout.error(f"{msg}")

def log_critical(msg):
  __cout.critical(f"{msg}")
