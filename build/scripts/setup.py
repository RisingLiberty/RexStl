import install_modules
import download_tools
import relocate_tools
import verify
import input

def main():
  install_modules.run()
  
  if not verify.verify_tools():
    download_tools.run()
    relocate_tools.run()
    
    print("Please add the directory provided to PATH environment variable.")
    input.ask("When finished, press Enter")

    while verify.run() == False:
      input.ask("Not all tools were found in PATH, please check..")
  
if __name__ == "__main__":
  main()