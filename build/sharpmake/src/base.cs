using System.IO;
using System.Linq;
using Sharpmake;
using System.Collections.Generic;
using System.Text.Json;
using System.Text;

// Represents the project that will be generated by Sharpmake and that contains
// the sample C++ code.
public class BaseProject : Project
{
  protected bool GenerateCompilerDB = true;

  public BaseProject() : base(typeof(RexTarget), typeof(RexConfiguration))
  {

  }

  [Configure]
  public virtual void Configure(RexConfiguration conf, RexTarget target)
  {
    conf.Name = target.Config.ToString().ToLower();
    conf.ProjectPath = Path.Combine(Globals.Root, ".rex", "build", GenerateSettings.IntermediateDir, target.DevEnv.ToString(), Name);
    conf.IntermediatePath = Path.Combine(conf.ProjectPath, "intermediate", conf.Name, target.Compiler.ToString());
    conf.TargetPath = Path.Combine(conf.ProjectPath, "bin", conf.Name);
    conf.UseRelativePdbPath = false;
    conf.LinkerPdbFilePath = Path.Combine(conf.TargetPath, $"{Name}_{conf.Name}_{target.Compiler}{conf.LinkerPdbSuffix}.pdb");
    conf.CompilerPdbFilePath = Path.Combine(conf.TargetPath, $"{Name}_{conf.Name}_{target.Compiler}{conf.CompilerPdbSuffix}.pdb");

    conf.DumpDependencyGraph = true;

    // workaround for rex_std
    if (Utils.FindInParent(SourceRootPath, "0_thirdparty") != "")
    {
      conf.SolutionFolder = "0_thirdparty";
    }

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
    //  conf.AddPublicDependency<SharpmakeProject>(target);
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
    return baseName;
  }

  protected void GenerateTargets()
  {
    if (GenerateSettings.EnableVisualStudio)
    {
      AddTargets(RexTarget.GetAllDefaultTargets());
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
    else if (GenerateSettings.GenerateFuzzyTests)
    {
      AddTargets(RexTarget.GetFuzzyTarget());
    }
    else
    {
      AddTargets(RexTarget.GetNinjaOnlyTarget());
    }
  }
}

public class BasicCPPProject : BaseProject
{
  protected string CompilerDBPath { get; set; }
  protected string GenerationConfigPath { get; set; }

  public override void PreConfigure()
  {
    base.PreConfigure();

    ReadGenerationConfigFile();
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    switch (target.Compiler)
    {
      case Compiler.MSVC:
        conf.add_public_define("REX_COMPILER_MSVC");
        break;
      case Compiler.Clang:
        conf.add_public_define("REX_COMPILER_CLANG");
        break;
      case Compiler.GCC:
        conf.add_public_define("REX_COMPILER_GCC");
        break;
      default:
        break;
    }

    switch (target.Config)
    {
      case Config.assert:
      case Config.debug:
      case Config.debug_opt:
        conf.add_public_define("REX_ENABLE_ASSERTS");
        break;
      case Config.release:
      case Config.tests:
      case Config.coverage:
      case Config.address_sanitizer:
      case Config.undefined_behavior_sanitizer:
      case Config.fuzzy:
        break;
    }

    if (target.Compiler == Compiler.Clang && (GenerateSettings.GenerateUnitTests == false && conf.is_config_for_testing() == false))
    {
      // setup post build command
      string compilerDBPath = GetClangToolsPath(conf);
      if (GenerateCompilerDB)
      {
        QueueCompilerDatabaseGeneration(conf);
        CopyClangToolConfigFiles(compilerDBPath);
      }
      else
      {
        string clangToolsPath = GetClangToolsOutputFolder(conf);
        if (Directory.Exists(clangToolsPath))
        {
          Directory.Delete(clangToolsPath, recursive: true);
        }
      }

      string postbuildCommandScriptPath = Path.Combine(Globals.SourceRoot, $"post_build.py");
      string postbuildCommandArguments = "";
      postbuildCommandArguments += $" -p={Name}";
      postbuildCommandArguments += $" -comp={target.Compiler}";
      postbuildCommandArguments += $" -conf={conf.Name}";
      postbuildCommandArguments += $" -compdb={compilerDBPath}";
      postbuildCommandArguments += $" -srcroot={SourceRootPath}";
      postbuildCommandArguments += $" -clang_tidy_regex=\"{GenerateSettings.ClangTidyRegex}\"";

      if (GenerateSettings.PerformAllChecks)
      {
        postbuildCommandArguments += $" -perform_all_checks";
      }

      if (GenerateSettings.NoClangTools == false)
      {
        postbuildCommandArguments += $" -use_clang_tools";
      }

      conf.EventPostBuild.Add($"py {postbuildCommandScriptPath}{postbuildCommandArguments}");
    }
  }

  protected string GetClangToolsPath(RexConfiguration conf)
  {
    return Path.Combine(conf.ProjectPath, "clang_tools", conf.Target.GetFragment<Compiler>().ToString(), conf.Name);
  }

  public override void PostLink()
  {
    base.PostLink();

    if (GenerateCompilerDB)
    {
      foreach (Configuration config in Configurations)
      {
        RexConfiguration rexConfig = config as RexConfiguration;
        RexTarget rexTarget = config.Target as RexTarget;
        if (rexTarget.Compiler == Compiler.Clang && rexConfig.is_config_for_testing() == false)
        {
          GenerateClangToolProjectFile(rexConfig, rexTarget);
        }
      }
    }
  }

  private void GenerateClangToolProjectFile(RexConfiguration conf, RexTarget target)
  {
    string clangToolsProjectPath = GetClangToolsPath(conf);

    ClangToolsProject project = new ClangToolsProject(Name, clangToolsProjectPath);
    project.HeaderFilters = conf.ClangToolHeaderFilterList.ToList();

    var options = new JsonSerializerOptions
    {
      WriteIndented = true
    };

    string jsonBlob = JsonSerializer.Serialize(project, options);

    if (!Directory.Exists(clangToolsProjectPath))
    {
      Directory.CreateDirectory(clangToolsProjectPath);
    }

    File.WriteAllText(project.ProjectPath, jsonBlob);
  }

  private void ReadGenerationConfigFile()
  {
    if (string.IsNullOrEmpty(GenerationConfigPath))
    {
      return;
    }

    if (!File.Exists(GenerationConfigPath))
    {
      System.Diagnostics.Debug.WriteLine($"Warning: GenerationConfigPath does not exist '{GenerationConfigPath}'");
      return;
    }

    string mem_tag_config_path = GenerationConfigPath;
    string json_blob = File.ReadAllText(mem_tag_config_path);
    Dictionary<string, EnumGenerationConfig> config = JsonSerializer.Deserialize<Dictionary<string, EnumGenerationConfig>>(json_blob);

    foreach (string key in config.Keys)
    {
      EnumGenerationConfig enum_config = config[key];
      
      if (!GenerateSettings.EnumsToAutoGenerate.ContainsKey(key))
      {
        GenerateSettings.EnumsToAutoGenerate.Add(key, new EnumGenerationSettings());

        // we use the config settings of the first enum we encounter, all others need to match this
        GenerateSettings.EnumsToAutoGenerate[key].ClassName = enum_config.ClassName;
        GenerateSettings.EnumsToAutoGenerate[key].Filepath = enum_config.Filepath;
      }
      else
      {
        EnumGenerationSettings enum_gen_settings = GenerateSettings.EnumsToAutoGenerate[key];

        // class names and filenames should be consistent among all generation files
        if (enum_gen_settings.ClassName != enum_config.ClassName)
        {
          throw new Error($"Enum generation error - unexpected classname: '{enum_config.ClassName}' - expected: {enum_gen_settings.ClassName} for project: {Name}");
        }

        if (enum_gen_settings.Filepath != enum_config.Filepath)
        {
          throw new Error($"Enum generation error - unexpected filepath: '{enum_config.Filepath}' - expected: {enum_gen_settings.Filepath} for project: {Name}");
        }
      }

      EnumGenerationSettings enum_gen_setting = GenerateSettings.EnumsToAutoGenerate[key];
      enum_gen_setting.ProjectToEnumValues.Add(Name, enum_config.Values);
    }
  }

  private string GetCompilerDBOutputPath(RexConfiguration config)
  {
    return $"{Path.Combine(GetCompilerDBOutputFolder(config), "compile_commands.json")}";
  }

  private string GetCompilerDBOutputFolder(RexConfiguration config)
  {
    return $"{Path.Combine(GetClangToolsOutputFolder(config), $"{PerConfigFolderFormat(config)}")}";
  }

  private string GetClangToolsOutputFolder(RexConfiguration config)
  {
    return $"{Path.Combine(config.ProjectPath, "clang_tools")}";
  }

  private static string PerConfigFolderFormat(RexConfiguration conf)
  {
    return Path.Combine(conf.Target.GetFragment<Compiler>().ToString(), conf.Name);
  }

  private void QueueCompilerDatabaseGeneration(RexConfiguration config)
  {
    string ninja_file_path = GetNinjaFilePath(config);
    string outputPath = GetCompilerDBOutputPath(config);

    string tools_json_path = Path.Combine(Globals.ToolsRoot, "tool_paths.json");
    string json_blob = File.ReadAllText(tools_json_path);
    Dictionary<string, string> paths = JsonSerializer.Deserialize<Dictionary<string, string>>(json_blob);

    string ninja_exe_filepath = paths["ninja_path"];

    // make sure the folder exists
    Directory.CreateDirectory(GetCompilerDBOutputFolder(config));

    System.Diagnostics.ProcessStartInfo start_info = new System.Diagnostics.ProcessStartInfo();
    start_info.FileName = "cmd.exe";
    start_info.Arguments = $"/C {ninja_exe_filepath} -f {ninja_file_path} compdb_{Name.ToLower()}_{config.Name}_clang --quiet > {outputPath}";
    start_info.RedirectStandardOutput = true;
    start_info.RedirectStandardError = true;
    start_info.UseShellExecute = false;


    System.Diagnostics.Process process = new System.Diagnostics.Process();
    process.StartInfo = start_info;
    GenerateSettings.GenerateCompilerDBProcesses.Add(process);
  }

  private void CopyClangToolConfigFiles(string compilerDBPath)
  {
    string clangTidyFirstPassFilename = ".clang-tidy_first_pass";
    string clangTidySecondPassFilename = ".clang-tidy_second_pass";
    string clangFormatFilename = ".clang-format";
    string iwyuFilename = "iwyu.imp";

    string clangTidyFirstPassSrcPath = Path.Combine(Utils.FindInParent(SourceRootPath, clangTidyFirstPassFilename), clangTidyFirstPassFilename);
    string clangTidySecondPassSrcPath = Path.Combine(Utils.FindInParent(SourceRootPath, clangTidySecondPassFilename), clangTidySecondPassFilename);
    string clangFormatSrcPath = Path.Combine(Utils.FindInParent(SourceRootPath, clangFormatFilename), clangFormatFilename);
    string iwyuSrcPath = Path.Combine(Utils.FindInParent(SourceRootPath, iwyuFilename), iwyuFilename);

    string clangTidyFirstPassDstPath = Path.Combine(compilerDBPath, clangTidyFirstPassFilename);
    string clangTidySecondPassDstPath = Path.Combine(compilerDBPath, clangTidySecondPassFilename);
    string clangFormatDstPath = Path.Combine(compilerDBPath, clangFormatFilename);
    string iwyuDstPath = Path.Combine(compilerDBPath, iwyuFilename);

    if (Directory.Exists(compilerDBPath) == false)
    {
      Directory.CreateDirectory(compilerDBPath);
    }

    File.Copy(clangTidyFirstPassSrcPath, clangTidyFirstPassDstPath, true);
    File.Copy(clangTidySecondPassSrcPath, clangTidySecondPassDstPath, true);
    File.Copy(clangFormatSrcPath, clangFormatDstPath, true);
    File.Copy(iwyuSrcPath, iwyuDstPath, true);
  }

  private string GetNinjaFilePath(RexConfiguration config)
  {
    return Path.Combine(config.ProjectPath, "ninja", GetPerConfigFileName(config, config.Target.GetFragment<Compiler>()));
  }
  private string GetPerConfigFileName(Project.Configuration config, Compiler compiler)
  {
    return $"{config.Project.Name}.{config.Name}.{compiler}.ninja";
  }
}

public class TestProject : BaseProject
{
  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    if (GenerateSettings.AddressSanitizerEnabled)
    {
      conf.add_public_define("CATCH_CONFIG_DISABLE"); // we don't need to check catch, it massively increase link time (47min at time of writing -> 5min)
    }
    else if (GenerateSettings.UndefinedBehaviorSanitizerEnabled)
    {
      conf.add_public_define("CATCH_CONFIG_DISABLE"); // we don't need to check catch, it massively increase link time (47min at time of writing -> 5min)
    }
  }
}

// All projects sitting in 0_thirdparty folder should inherit from this
public class ThirdPartyProject : BasicCPPProject
{
  public ThirdPartyProject() : base()
  {
    GenerateCompilerDB = false;
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.SolutionFolder = "0_thirdparty";
  }
}

// All projects sitting in 1_engine folder should inherit from this
public class EngineProject : BasicCPPProject
{
  public EngineProject() : base()
  { }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.SolutionFolder = "1_engine";
  }
}

// All projects sitting in 2_platform folder should inherit from this
public class PlatformProject : BasicCPPProject
{
  public PlatformProject() : base()
  { }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.SolutionFolder = "2_platform";
  }
}

// All projects sitting in 3_app_libs folder should inherit from this
public class AppLibrariesProject : BasicCPPProject
{
  public AppLibrariesProject() : base()
  { }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.SolutionFolder = "3_app_libs";
  }
}

// All projects sitting in 5_tools folder should inherit from this
public class ToolsProject : BasicCPPProject
{
  public ToolsProject() : base()
  { }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.SolutionFolder = "4_tools";
  }
}