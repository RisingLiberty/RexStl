using System.IO;
using System.Linq;
using Sharpmake;
using System;
using System.Collections.Generic;

namespace rex
{
  // The sharpmake project that generates the solution
  // It makes life a lot easier if this is directly in the solution.
  [Generate]
  public class SharpmakeProject : BasicCSProject
  {
    public SharpmakeProject() : base()
    {
      Name = "SharpmakeProject";
      SourceFilesExtensions.Clear();
      SourceFilesExtensions.Add(".sharpmake.cs");
      SourceRootPath = Path.Combine(Globals.Root);

      // Ignore the data folder, this folder can become very big
      // and will never contain any sharpmake files
      SourceFilesExcludeRegex.Add("data");

      // ignore the templates folder, these are used for auto generation, shouldn't be added to the project itself
      SourceFilesExcludeRegex.Add("templates");

      // manually add the sharpmake root files
      var RootSharpmakeFiles = Directory.GetFiles(Path.Combine(Globals.SharpmakeRoot, "src"), "*.cs", SearchOption.AllDirectories);
      foreach (var File in RootSharpmakeFiles)
      {
        SourceFiles.Add(File);
      }

      RexTarget vsTarget = new RexTarget(Platform.win64, ProjectGen.Settings.IDE.ToDevEnv(), Config.debug | Config.debug_opt | Config.release, Compiler.MSVC);

      // Specify the targets for which we want to generate a configuration for.
      AddTargets(vsTarget);
    }

    protected override void SetupSolutionFolder(RexConfiguration conf, RexTarget target)
    {
      base.SetupSolutionFolder(conf, target);

      conf.SolutionFolder = "_Generation";
    }

    protected override void SetupOutputType(RexConfiguration conf, RexTarget target)
    {
      conf.Output = Configuration.OutputType.DotNetClassLibrary;
    }

    // Setup default configuration settings for C++ projects
    protected override void SetupConfigSettings(RexConfiguration conf, RexTarget target)
    {
      base.SetupConfigSettings(conf, target);

      conf.StartWorkingDirectory = Globals.SharpmakeRoot;
    }

    protected override void SetupLibDependencies(RexConfiguration conf, RexTarget target)
    {
      base.SetupLibDependencies(conf, target);

      string sharpmakeAppPath = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
      string sharpmakeDllPath = Path.Combine(Path.GetDirectoryName(sharpmakeAppPath), "sharpmake.dll");

      conf.ReferencesByPath.Add(sharpmakeDllPath);
      conf.ReferencesByName.AddRange(new Strings("System",
                                                 "System.Core",
                                                 "System.Memory"
                                                 ));

      conf.ReferencesByNuGetPackage.Add("System.Text.Json", "5.0.2"); // same version sharpmake uses

      List<string> listOfArgs = Environment.GetCommandLineArgs().ToList();
      listOfArgs.RemoveAt(0); // Removing the first argument as it's the path to sharpmake
      string argsAsString = string.Join(" ", listOfArgs);

      // Surround all arguments within brackets with quotes
      int openingBracketPos = argsAsString.IndexOf("(");
      if (openingBracketPos == -1)
      {
        return;
      }

      string args = ConvertArgumentsForSharpmake(argsAsString);

      conf.CsprojUserFile = new Configuration.CsprojUserFileSettings();
      conf.CsprojUserFile.StartAction = Configuration.CsprojUserFileSettings.StartActionSetting.Program;
      conf.CsprojUserFile.StartArguments = $@"{args}";
      conf.CsprojUserFile.StartProgram = sharpmakeAppPath;
      conf.CsprojUserFile.WorkingDirectory = Directory.GetCurrentDirectory();
    }

    private string ConvertArgumentsForSharpmake(string inArgs)
    {
      if (string.IsNullOrEmpty(inArgs))
      {
        return inArgs;
      }

      // If there's not '(' in the argument, we don't need to convert anything
      int openBracketPos = inArgs.IndexOf("(");
      if (openBracketPos == -1)
      {
        return inArgs;
      }

      string result = "";

      // Surround every arguments within brackets with quotes
      int closeBracketPos = inArgs.IndexOf(")");
      int start = 0;

      while (openBracketPos != -1 && closeBracketPos != -1)
      {
        string argumentsWithinBrackets = inArgs.Substring(openBracketPos + 1, (closeBracketPos - openBracketPos) - 1);

        // First add everything that's before the opening bracket
        result += inArgs.Substring(start, (openBracketPos - start) + 1); // +1 to add the brace itself

        // Split anything that's between brackets and add the quotes if they're not already there
        List<string> splittedArgumentsWithinBrackets = argumentsWithinBrackets.Split(new char[] { ',' }).ToList();
        foreach (string arg in splittedArgumentsWithinBrackets)
        {
          string argToAdd = arg;
          if (!arg.StartsWith("\"") && !arg.EndsWith("\""))
          {
            argToAdd = $"\"{arg}\"";
          }
          
          result += argToAdd;
          result += ",";
        }

        // pop the last comma
        result = result.Remove(result.Length - 1);

        // scan for the next argument within brackets
        start = closeBracketPos;
        openBracketPos = inArgs.IndexOf("(", closeBracketPos + 1);
        closeBracketPos = inArgs.IndexOf(")", closeBracketPos + 1);
      }

      result += inArgs.Substring(start);

      return result;
    }
  }
}