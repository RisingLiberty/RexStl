// ============================================ 
//
// REX - BUILD SYSTEM
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: main.sharpmake.cs
// Copyright (c) Nick De Breuck 2022
//
// ============================================

using System.IO;
using System.Linq;
using Sharpmake;

[module: Sharpmake.Include("config.sharpmake.cs")]

public class Globals
{
  static readonly private string folder_in_root = "source";
  static private string root;
  static private string source_root;

  static public string Root
  {
    get
    {
      return root;
    }
  }
  static public string SourceRoot
  {
    get
    {
      return source_root;
    }
  }

  static public void Init()
  {
    string current_directory = Directory.GetCurrentDirectory();

    while (Directory.GetDirectories(current_directory).ToList().FindIndex(x => Path.GetFileName(x) == folder_in_root) == -1)
    {
      if (Directory.GetDirectoryRoot(current_directory) == current_directory)
      {
        throw new System.Exception("Failed to find root directory");
      }
      current_directory = Directory.GetParent(current_directory).FullName;
    }

    root = current_directory;
    source_root = Path.Combine(root, "source");
    System.Console.WriteLine($"Root path:{root}");
  }
}

[Fragment, System.Flags]
public enum Optimization
{
  NoOpt = (1 << 0),
  FullOptWithPdb = (1 << 1),
  FullOpt = (1 << 2)
}

public class RexTarget : ITarget
{
  public DevEnv DevEnv;
  public Platform Platform;
  public Config Config;
  public Compiler Compiler;
  public RexTarget()
  { }
  public RexTarget(Platform platform, DevEnv devEnv, Config config, Compiler compiler)
  {
    DevEnv = devEnv;
    Platform = platform;
    Config = config;
    Compiler = compiler;
  }

  // This is the display name of the configuration dropdown in visual studio
  public override string Name
  {
    get
    {
      string config_str = string.Concat(Config.ToString().ToString().Select((x, i) => i > 0 && char.IsUpper(x) ? "_" + x.ToString() : x.ToString()));

      return (config_str).ToLowerInvariant();
    }
  }

  public Optimization Optimization
  {
    get { return ConfigManager.get_optimization_for_config(Config); }
  }
}

public class RexConfiguration : Sharpmake.Project.Configuration
{
  public RexConfiguration()
  {
  }

  public void enable_exceptions()
  {
    Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Enable);
    Defines.Add("_HAS_EXCEPTIONS=1");
  }

  public void disable_exceptions()
  {
    Options.Add(Sharpmake.Options.Vc.Compiler.Exceptions.Disable);
    Defines.Add("_HAS_EXCEPTIONS=0");
  }

  public void use_general_options()
  {
    //Options.Add(Sharpmake.Options.Vc.General.JumboBuild.Enable);
    Options.Add(Sharpmake.Options.Vc.General.CharacterSet.MultiByte);
    Options.Add(Sharpmake.Options.Vc.General.PlatformToolset.v142);
    //Options.Add(Sharpmake.Options.Vc.General.VCToolsVersion.v14_21_27702);
    Options.Add(Sharpmake.Options.Vc.General.WarningLevel.Level4);
    Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
  }

  public void use_compiler_options()
  {
    Options.Add(Sharpmake.Options.Vc.Compiler.SupportJustMyCode.No); // this adds a call to __CheckForDebuggerJustMyCode into every function that slows down runtime significantly
    Options.Add(Sharpmake.Options.Vc.Compiler.CppLanguageStandard.CPP17);
    Options.Add(Sharpmake.Options.Vc.Compiler.RTTI.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Default);
    Options.Add(Sharpmake.Options.Vc.Compiler.FloatingPointModel.Fast);
    Options.Add(Sharpmake.Options.Vc.Compiler.MultiProcessorCompilation.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.StringPooling.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.BufferSecurityCheck.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.FunctionLevelLinking.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.FloatingPointExceptions.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.OpenMP.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.JumboBuild.Enable);
  }

  public void use_linker_options()
  {
    Options.Add(Sharpmake.Options.Vc.Linker.LargeAddress.SupportLargerThan2Gb);
    Options.Add(Sharpmake.Options.Vc.Linker.GenerateMapFile.Disable);
    Options.Add(Sharpmake.Options.Vc.Linker.GenerateManifest.Disable);
    Options.Add(Sharpmake.Options.Vc.Linker.TreatLinkerWarningAsErrors.Enable);
  }

  public void enable_optimization()
  {
    Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.MaximizeSpeed);
    Options.Add(Sharpmake.Options.Vc.Compiler.Intrinsic.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeLibrary.MultiThreaded);
    Options.Add(Sharpmake.Options.Vc.Compiler.Inline.AnySuitable);
    Options.Add(Sharpmake.Options.Vc.Compiler.FiberSafe.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Default);

    Options.Add(Sharpmake.Options.Vc.Compiler.MinimalRebuild.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.FavorSizeOrSpeed.FastCode);
    Options.Add(Sharpmake.Options.Vc.Compiler.FunctionLevelLinking.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.OmitFramePointers.Enable);

    Options.Add(Sharpmake.Options.Vc.Linker.LinkTimeCodeGeneration.UseLinkTimeCodeGeneration);
    Options.Add(Sharpmake.Options.Vc.Linker.EnableCOMDATFolding.RemoveRedundantCOMDATs);
    Options.Add(Sharpmake.Options.Vc.Linker.Reference.EliminateUnreferencedData);
    //Options.Add(Sharpmake.Options.Vc.Linker.Incremental.Enable);
  }

  public void disable_optimization()
  {
    Defines.Add("USING_DEBUG_RUNTIME_LIBS");

    Options.Add(Sharpmake.Options.Vc.Compiler.Optimization.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.Intrinsic.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebug);
    Options.Add(Sharpmake.Options.Vc.Compiler.Inline.Default);
    Options.Add(Sharpmake.Options.Vc.Compiler.FiberSafe.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.RuntimeChecks.Both);
    Options.Add(Sharpmake.Options.Vc.Compiler.MinimalRebuild.Enable);
    Options.Add(Sharpmake.Options.Vc.Compiler.FavorSizeOrSpeed.Neither);
    Options.Add(Sharpmake.Options.Vc.Compiler.OmitFramePointers.Disable);
    Options.Add(Sharpmake.Options.Vc.Compiler.FunctionLevelLinking.Enable);

    Options.Add(Sharpmake.Options.Vc.Linker.LinkTimeCodeGeneration.Default);
    Options.Add(Sharpmake.Options.Vc.Linker.EnableCOMDATFolding.DoNotRemoveRedundantCOMDATs);
    Options.Add(Sharpmake.Options.Vc.Linker.CreateHotPatchableImage.Enable);
    Options.Add(Sharpmake.Options.Vc.Linker.Incremental.Enable);
    //Options.Add(Sharpmake.Options.Vc.Linker.GenerateDebugInformation.Enable);
  }

  public void add_dependency<TPROJECT>(ITarget target)
  {
    AddPublicDependency<TPROJECT>(target, DependencySetting.Default | DependencySetting.Defines);
  }

  public void add_public_define(string define)
  {
    Defines.Add(define);
    ExportDefines.Add(define);
  }

  public void set_precomp_header(string projectFolderName, string preCompHeaderName)
  {
    PrecompHeader = projectFolderName + @"/" + preCompHeaderName + @".h";
    PrecompSource = preCompHeaderName + @".cpp";
  }
}

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

    if (target.Compiler == Compiler.MSVC)
    {
      conf.IncludeSystemPaths.Add(@"D:\Tools\Windows SDK\10.0.19041.0\include\um");
      conf.IncludeSystemPaths.Add(@"D:\Tools\Windows SDK\10.0.19041.0\include\shared");
      conf.IncludeSystemPaths.Add(@"D:\Tools\Windows SDK\10.0.19041.0\include\winrt");
      conf.IncludeSystemPaths.Add(@"D:\Tools\Windows SDK\10.0.19041.0\include\cppwinrt");
      conf.IncludeSystemPaths.Add(@"D:\Tools\Windows SDK\10.0.19041.0\include\ucrt");
      conf.IncludeSystemPaths.Add(@"D:\Tools\MSVC\install\14.29.30133\include");
      conf.IncludeSystemPaths.Add(@"D:\Tools\MSVC\install\14.29.30133\atlmfc\include");
    }

    if (target.Compiler == Compiler.GCC && conf.Output == Configuration.OutputType.Dll) // Sharpmake doesn't support DLLs for GCC
    {
      conf.Output = Configuration.OutputType.Lib;
    }

    conf.IncludePaths.Add($@"{SourceRootPath}\include");

    string postbuildCommandScript = Path.Combine(Globals.Root, "build", "scripts", $"post_build.py -p={Name} -comp={target.Compiler} -conf={conf.Name}");

    conf.EventPostBuild.Add(postbuildCommandScript);

    conf.disable_exceptions();

    conf.use_general_options();
    conf.use_compiler_options();
    conf.use_linker_options();

    switch (target.Optimization)
    {
      case Optimization.NoOpt:
        conf.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabase);
        conf.disable_optimization();
        break;
      case Optimization.FullOptWithPdb:
        conf.Options.Add(Options.Vc.General.DebugInformation.ProgramDatabase);
        conf.enable_optimization();
        conf.Options.Add(Options.Vc.Linker.LinkTimeCodeGeneration.Default);      // To fix linker warning
        conf.Options.Add(Options.Vc.Compiler.OmitFramePointers.Disable);         // Disable so we can have a stack trace
        break;
      case Optimization.FullOpt:
        conf.Options.Add(Options.Vc.General.DebugInformation.Disable);
        conf.Options.Add(Options.Vc.General.WholeProgramOptimization.Optimize);
        conf.enable_optimization();
        break;
    }
  }

}

[Generate]
public class AppProject : BaseProject
{
  public AppProject() : base()
  {
    // The name of the project in Visual Studio. The default is the name of
    // the class, but you usually want to override that.
    Name = "RexStdExe";

    // The directory that contains the source code we want to build is the
    // same as this one. This string essentially means "the directory of
    // the script you're reading right now."
    SourceRootPath = Path.Combine(Globals.SourceRoot, "RexStdExe");

    RexTarget vsTarget = new RexTarget(Platform.win64, DevEnv.vs2019, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC);
    RexTarget ninjaTarget = new RexTarget(Platform.win64, DevEnv.ninja, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC | Compiler.Clang);

    // Specify the targets for which we want to generate a configuration for.
    AddTargets(vsTarget, ninjaTarget);
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.Output = Configuration.OutputType.Exe;

    conf.add_dependency<LibProject>(target);
  }
}

[Generate]
public class LibProject : BaseProject
{
  public LibProject() : base()
  {
    // The name of the project in Visual Studio. The default is the name of
    // the class, but you usually want to override that.
    Name = "RexStd";

    // The directory that contains the source code we want to build is the
    // same as this one. This string essentially means "the directory of
    // the script you're reading right now."
    SourceRootPath = Path.Combine(Globals.SourceRoot, "RexStd");

    RexTarget vsTarget = new RexTarget(Platform.win64, DevEnv.vs2019, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC);
    RexTarget ninjaTarget = new RexTarget(Platform.win64, DevEnv.ninja, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC | Compiler.Clang);

    // Specify the targets for which we want to generate a configuration for.
    AddTargets(vsTarget, ninjaTarget);
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.Output = Configuration.OutputType.Lib;

    switch (conf.Platform)
    {
      case Platform.win32:
        conf.add_public_define("REX_PLATFORM_X86");
        break;
      case Platform.win64:
        conf.add_public_define("REX_PLATFORM_X64");
        break;
      default:
        break;
    }
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
    Name = "rex-standard-library";

    // As with the project, define which target this solution builds for.
    // It's usually the same thing.
    RexTarget vsTarget = new RexTarget(Platform.win64, DevEnv.vs2019, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC);
    RexTarget ninjaTarget = new RexTarget(Platform.win64, DevEnv.ninja, Config.debug | Config.debug_opt | Config.release, Compiler.MSVC | Compiler.Clang);

    // Specify the targets for which we want to generate a configuration for.
    AddTargets(vsTarget, ninjaTarget);
  }

  // Configure for all 4 generated targets. Note that the type of the
  // configuration object is of type Solution.Configuration this time.
  // (Instead of Project.Configuration.)
  [Configure]
  public void Configure(Configuration conf, RexTarget target)
  {
    // Puts the generated solution in the root folder.
    conf.SolutionPath = Globals.Root;

    // Adds the project described by BasicsProject into the solution.
    // Note that this is done in the configuration, so you can generate
    // solutions that contain different projects based on their target.
    //
    // You could, for example, exclude a project that only supports 64-bit
    // from the 32-bit targets.
    conf.AddProject<AppProject>(target);
  }
}

public static class Main
{
  [Sharpmake.Main]
  public static void SharpmakeMain(Arguments arguments)
  {
    Globals.Init();

    InitializeSharpmake();

    // Tells Sharpmake to generate the solution described by MainSolution.
    arguments.Generate<MainSolution>();
  }

  private static void InitializeSharpmake()
  {
    KitsRootPaths.InitializeForNinja();

    // Initialize Visual Studio settings
    KitsRootPaths.SetUseKitsRootForDevEnv(DevEnv.vs2019, KitsRootEnum.KitsRoot10, Options.Vc.General.WindowsTargetPlatformVersion.v10_0_19041_0);
  }
}