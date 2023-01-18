// ============================================ 
//
// REX - BUILD SYSTEM
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: main.sharpmake.cs
// Copyright (c) Nick De Breuck 2023
//
// ============================================

using System.IO;
using System.Linq;
using Sharpmake;
using System;
using System.Collections.Generic;
using System.Text.Json;

[module: Sharpmake.Reference("System.Text.Json.dll")]
[module: Sharpmake.Reference("System.Memory.dll")]

// Represents the project that will be generated by Sharpmake and that contains
// the sample C++ code.
public class BaseProject : Project
{
  public BaseProject() : base(typeof(RexTarget), typeof(RexConfiguration))
  {
    
  }

  [Configure]
  public virtual void Configure(RexConfiguration conf, RexTarget target)
  {
    conf.Name = target.Config.ToString().ToLower();
    conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "build", target.DevEnv.ToString(), Name);
    conf.IntermediatePath = Path.Combine(conf.ProjectPath, "intermediate", conf.Name, target.Compiler.ToString());
    conf.TargetPath = Path.Combine(conf.ProjectPath, "bin", conf.Name);
    conf.UseRelativePdbPath = false;
    conf.LinkerPdbFilePath = Path.Combine(conf.TargetPath, $"{Name}_{conf.Name}_{target.Compiler}{conf.LinkerPdbSuffix}.pdb");
    conf.CompilerPdbFilePath = Path.Combine(conf.TargetPath, $"{Name}_{conf.Name}_{target.Compiler}{conf.CompilerPdbSuffix}.pdb");

    if (conf.Compiler == DevEnv.ninja && target.Compiler == Compiler.MSVC)
    {
      string tools_json_path = Path.Combine(Globals.LibsRoot, "lib_paths.json");
      string json_blob = File.ReadAllText(tools_json_path);
      Dictionary<string, string[]> paths = JsonSerializer.Deserialize<Dictionary<string, string[]>>(json_blob);

      List<string> include_paths = new List<string>();
      include_paths.AddRange(paths["windows_sdk_includes"].ToList());
      include_paths.AddRange(paths["msvc_includes"].ToList());
      foreach (var path in include_paths)
      {
        conf.IncludeSystemPaths.Add(path);
      }

      List<string> lib_paths = new List<string>();
      lib_paths.AddRange(paths["windows_sdk_lib"].ToList());
      lib_paths.AddRange(paths["msvc_libs"].ToList());
      foreach (var path in lib_paths)
      {
        conf.LibraryPaths.Add(path);
      }
    }

    if (target.Compiler == Compiler.GCC && conf.Output == Configuration.OutputType.Dll) // Sharpmake doesn't support DLLs for GCC
    {
      conf.Output = Configuration.OutputType.Lib;
    }

    if (target.Config == Config.coverage)
    {
      conf.NinjaGenerateCodeCoverage = true;
    }

    if (target.Config == Config.address_sanitizer)
    {
      conf.NinjaEnableAddressSanitizer = true;
    }

    if (target.Config == Config.undefined_behavior_sanitizer)
    {
      conf.NinjaEnableUndefinedBehaviorSanitizer = true;
    }

    if (target.Config == Config.fuzzy)
    {
      conf.NinjaEnableAddressSanitizer = true;
      conf.NinjaEnableUndefinedBehaviorSanitizer = true;
      conf.NinjaEnableFuzzyTesting = true;
    }

    conf.IncludePaths.Add($@"{SourceRootPath}\include");

    conf.disable_exceptions();

    conf.use_general_options();
    conf.use_compiler_options();
    conf.use_linker_options();

    //if (target.DevEnv == DevEnv.vs2019)
    //{
    //  conf.add_dependency<SharpmakeProject>(target);
    //}

    switch (target.Optimization)
    {
      case Optimization.NoOpt:
        conf.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabase);
        conf.disable_optimization();
        break;
      case Optimization.FullOptWithPdb:
        conf.enable_optimization();
        conf.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabase);
        conf.Options.Add(Options.Vc.Compiler.OmitFramePointers.Disable);         // Disable so we can have a stack trace
        break;
      case Optimization.FullOpt:
        conf.Options.Add(Options.Vc.General.DebugInformation.Disable);
        conf.Options.Add(Options.Vc.General.WholeProgramOptimization.Optimize);
        conf.enable_optimization();
        break;
    }

    switch (target.Platform)
    {
      case Platform.win32:
      case Platform.win64:
        conf.add_public_define("REX_PLATFORM_WINDOWS");
        break;
      default:
        break;
    }
  }

  protected string GenerateName(string baseName)
  {
    if (GenerateSettings.CoverageEnabled)
    {
      baseName += "_coverage";
    }
    else if (GenerateSettings.AddressSanitizerEnabled)
    {
      baseName += "_asan";
    }
    else if (GenerateSettings.UndefinedBehaviorSanitizerEnabled)
    {
      baseName += "_ubsan";
    }
    else if (GenerateSettings.FuzzyTestingEnabled)
    {
      baseName += "_fuzzy";
    }

    return baseName;
  }

  protected void GenerateTargets()
  {
    if (GenerateSettings.VisualStudioOnly)
    {
      AddTargets(RexTarget.GetVsOnlyTarget());
    }
    else if (GenerateSettings.CoverageEnabled)
    {
      AddTargets(RexTarget.GetCoverageTarget());
    }
    else if (GenerateSettings.AddressSanitizerEnabled)
    {
      AddTargets(RexTarget.GetAsanTarget());
    }
    else if (GenerateSettings.UndefinedBehaviorSanitizerEnabled)
    {
      AddTargets(RexTarget.GetUBsanTarget());
    }
    else if (GenerateSettings.FuzzyTestingEnabled)
    {
      AddTargets(RexTarget.GetFuzzyTarget());
    }
    else
    {
      AddTargets(RexTarget.GetDefaultTargets());
    }
  }
}

public class BasicCPPProject : BaseProject
{
  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);
  }
}

public class TestProject : BaseProject
{
  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    if (GenerateSettings.CoverageEnabled)
    {
      conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "tests", "coverage", "build", target.DevEnv.ToString(), Name);
    }
    else if (GenerateSettings.AddressSanitizerEnabled)
    {
      conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "tests", "asan", "build", target.DevEnv.ToString(), Name);
      conf.add_public_define("CATCH_CONFIG_DISABLE"); // we don't need to check catch, it massively increase link time (47min at time of writing -> 5min)
    }
    else if (GenerateSettings.UndefinedBehaviorSanitizerEnabled)
    {
      conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "tests", "ubsan", "build", target.DevEnv.ToString(), Name);
      conf.add_public_define("CATCH_CONFIG_DISABLE"); // we don't need to check catch, it massively increase link time (47min at time of writing -> 5min)
    }
    else if (GenerateSettings.FuzzyTestingEnabled)
    {
      conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "tests", "fuzzy", "build", target.DevEnv.ToString(), Name);
    }
    else
    {
      conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "tests", "build", target.DevEnv.ToString(), Name);
    }
    
    conf.IntermediatePath = Path.Combine(conf.ProjectPath, "intermediate", conf.Name, target.Compiler.ToString());
    conf.TargetPath = Path.Combine(conf.ProjectPath, "bin", conf.Name);
    conf.UseRelativePdbPath = false;
    conf.LinkerPdbFilePath = Path.Combine(conf.TargetPath, $"{Name}_{conf.Name}_{target.Compiler}{conf.LinkerPdbSuffix}.pdb");
    conf.CompilerPdbFilePath = Path.Combine(conf.TargetPath, $"{Name}_{conf.Name}_{target.Compiler}{conf.CompilerPdbSuffix}.pdb");
  }
}

// The sharpmake project that generates the solution
// It makes life a lot easier if this is directly in the solution.
[Generate]
public class SharpmakeProject : CSharpProject
{
  public SharpmakeProject() : base(typeof(RexTarget), typeof(RexConfiguration))
  {
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

  [Configure()]
  public virtual void Configure(RexConfiguration conf, RexTarget target)
  {
    conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "build", target.DevEnv.ToString(), Name);
    conf.IntermediatePath = Path.Combine(conf.ProjectPath, "intermediate", conf.Name, target.Compiler.ToString());
    conf.TargetPath = Path.Combine(conf.ProjectPath, "bin", conf.Name);
    conf.Output = Configuration.OutputType.DotNetClassLibrary;
    conf.StartWorkingDirectory = Globals.SharpmakeRoot;

    string sharpmakeAppPath = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
    string sharpmakeDllPath = Path.Combine(Path.GetDirectoryName(sharpmakeAppPath), "sharpmake.dll");

    conf.ReferencesByPath.Add(sharpmakeDllPath);
    conf.ReferencesByName.AddRange(new Strings("System",
                                               "System.Core",
                                               "System.Memory"
                                               ));

    conf.ReferencesByNuGetPackage.Add("System.Text.Json", "5.0.2"); // same version sharpmake uses

    conf.CsprojUserFile = new Configuration.CsprojUserFileSettings();
    conf.CsprojUserFile.StartAction = Configuration.CsprojUserFileSettings.StartActionSetting.Program;

    string quote = "\'"; // Use single quote that is cross platform safe
    string sharpmake_main = Path.Combine(Globals.SharpmakeRoot, "src", "main.sharpmake.cs");
    sharpmake_main = sharpmake_main.Replace('\\', '/');
    conf.CsprojUserFile.StartArguments = $@"/sources(@{quote}{sharpmake_main}{quote}) /diagnostics";
    conf.CsprojUserFile.StartProgram = sharpmakeAppPath;
    conf.CsprojUserFile.WorkingDirectory = Directory.GetCurrentDirectory();
  }
}

// Represents the solution that will be generated and that will contain the
// project with the sample code.
[Generate]
public class MainSolution : Solution
{
  public MainSolution() : base(typeof(RexTarget))
  {
    // The name of the solution.
    Name = GenerateName("rex-standard-library");
    GenerateTargets();
  }

  // Configure for all 4 generated targets. Note that the type of the
  // configuration object is of type Solution.Configuration this time.
  // (Instead of Project.Configuration.)
  [Configure]
  public void Configure(Configuration conf, RexTarget target)
  {
    // Puts the generated solution in the root folder.
    conf.SolutionPath = Globals.Root;

    if (target.DevEnv == DevEnv.vs2019)
    {
      conf.AddProject<SharpmakeProject>(target);
    }

    conf.AddProject<RexStd>(target);

    if (GenerateSettings.UnitTestsEnabled)
    {
      conf.AddProject<RexStdTest>(target);
    }

    if (GenerateSettings.FuzzyTestingEnabled)
    {
      conf.AddProject<RexStdFuzzy>(target);
    }
    else
    {
      conf.AddProject<RexStdExe>(target);
    }
  }

  protected string GenerateName(string baseName)
  {
    if (GenerateSettings.CoverageEnabled)
    {
      baseName += "_coverage";
    }
    else if (GenerateSettings.AddressSanitizerEnabled)
    {
      baseName += "_asan";
    }
    else if (GenerateSettings.UndefinedBehaviorSanitizerEnabled)
    {
      baseName += "_ubsan";
    }
    else if (GenerateSettings.FuzzyTestingEnabled)
    {
      baseName += "_fuzzy";
    }

    return baseName;
  }

  protected void GenerateTargets()
  {
    if (GenerateSettings.VisualStudioOnly)
    {
      AddTargets(RexTarget.GetVsOnlyTarget());
    }
    else if (GenerateSettings.CoverageEnabled)
    {
      AddTargets(RexTarget.GetCoverageTarget());
    }
    else if (GenerateSettings.AddressSanitizerEnabled)
    {
      AddTargets(RexTarget.GetAsanTarget());
    }
    else if (GenerateSettings.UndefinedBehaviorSanitizerEnabled)
    {
      AddTargets(RexTarget.GetUBsanTarget());
    }
    else if (GenerateSettings.FuzzyTestingEnabled)
    {
      AddTargets(RexTarget.GetFuzzyTarget());
    }
    else
    {
      AddTargets(RexTarget.GetDefaultTargets());
    }
  }
}

public static class Main
{
  [Sharpmake.Main]
  public static void SharpmakeMain(Arguments arguments)
  {
    Globals.Init();

    InitializeSharpmake();
    InitializeSettings();

    arguments.Generate<MainSolution>();
  }

  private static void InitializeSharpmake()
  {
    InitializeNinja();

    // Initialize Visual Studio settings
    KitsRootPaths.SetUseKitsRootForDevEnv(DevEnv.vs2019, KitsRootEnum.KitsRoot10, Options.Vc.General.WindowsTargetPlatformVersion.v10_0_19041_0);
  }

  private static void InitializeNinja()
  {
    string tools_json_path = Path.Combine(Globals.ToolsRoot, "tool_paths.json");
    string json_blob = File.ReadAllText(tools_json_path);
    Dictionary<string, string> paths = JsonSerializer.Deserialize<Dictionary<string, string>>(json_blob);

    KitsRootPaths.SetCompilerPaths(Compiler.MSVC, paths["msvc_compiler_path"], paths["msvc_linker_path"], paths["msvc_archiver_path"], "");
    KitsRootPaths.SetCompilerPaths(Compiler.Clang, paths["clang_compiler_path"], paths["clang_linker_path"], paths["clang_archiver_path"], paths["clang_ranlib_path"]);
    KitsRootPaths.SetNinjaPath(paths["ninja_path"]);
  }

  private static void InitializeSettings()
  {
    GenerateSettings.UnitTestsEnabled = CommandLine.GetParameters().ToList().FindIndex(x => x.ToString() == "/generateUnitTests") != -1;
    GenerateSettings.CoverageEnabled = CommandLine.GetParameters().ToList().FindIndex(x => x.ToString() == "/enableCoverage") != -1;
    GenerateSettings.AddressSanitizerEnabled = CommandLine.GetParameters().ToList().FindIndex(x => x.ToString() == "/enableAddressSanitizer") != -1;
    GenerateSettings.UndefinedBehaviorSanitizerEnabled = CommandLine.GetParameters().ToList().FindIndex(x => x.ToString() == "/enableUBSanitizer") != -1;
    GenerateSettings.FuzzyTestingEnabled = CommandLine.GetParameters().ToList().FindIndex(x => x.ToString() == "/enableFuzzyTesting") != -1;
    GenerateSettings.VisualStudioOnly = CommandLine.GetParameters().ToList().FindIndex(x => x.ToString() == "/vsOnly") != -1;
  }
}