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
      SourceRootPath = Globals.Root;

      // manually add the sharpmake root files
      var RootSharpmakeFiles = Directory.GetFiles(Path.Combine(Globals.SharpmakeRoot, "src"));
      foreach (var File in RootSharpmakeFiles)
      {
        SourceFiles.Add(File);
      }

      RexTarget vsTarget = new RexTarget(Platform.win64, DevEnv.vs2019, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC);

      // Specify the targets for which we want to generate a configuration for.
      AddTargets(vsTarget);
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

      conf.CsprojUserFile = new Configuration.CsprojUserFileSettings();
      conf.CsprojUserFile.StartAction = Configuration.CsprojUserFileSettings.StartActionSetting.Program;
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

      string quote = "\'"; // Use single quote that is cross platform safe
      List<string> sharpmake_sources = new List<string>();
      foreach (string sourceFile in SourceFiles)
      {
        string file = sourceFile.Replace('\\', '/');
        sharpmake_sources.Add($"{quote}{file}{quote}");
      }

      foreach (string file in Directory.EnumerateFiles(SourceRootPath, "*.*", SearchOption.AllDirectories))
      {
        if (file.EndsWith(".sharpmake.cs"))
        {
          string fileWithSlashes = file.Replace('\\', '/');
          sharpmake_sources.Add($"{quote}{fileWithSlashes}{quote}");
        }
      }

      string sourcesArg = @"/sources(";
      foreach (string file in sharpmake_sources)
      {
        sourcesArg += file;
        sourcesArg += ", ";
      }
      sourcesArg = sourcesArg.Substring(0, sourcesArg.Length - 2); // remove ", ";
      sourcesArg += ")";

      conf.CsprojUserFile.StartArguments = $@"{sourcesArg} /diagnostics";
      conf.CsprojUserFile.StartProgram = sharpmakeAppPath;
      conf.CsprojUserFile.WorkingDirectory = Directory.GetCurrentDirectory();
    }
  }
}