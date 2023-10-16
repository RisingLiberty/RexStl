using System.IO;
using Sharpmake;
using System;
using System.Collections.Generic;
using System.Text.Json;

[module: Sharpmake.Reference("System.Text.Json.dll")]
[module: Sharpmake.Reference("System.Memory.dll")]

namespace rex
{
  // The commandline arguments possible to give to sharpmake
  // Each argument must be prefixed with '/' and it's value must between brackets (eg. /configFile("data/config.json"))
  // The default config file is found in data/default_config.json of where this script is located.
  public class CmdLineArguments
  {
    [Sharpmake.CommandLine.Option("configFile", "Path to the config file meant to be read by Sharpmake.")]
    public void CommandLineConfigFile(string configFileDir)
    {
      ProjectGen.Settings.ConfigFileDir = configFileDir;
    }
  }
}

public static class Main
{
  // This is the entry point called from the Sharpmake executable
  [Sharpmake.Main]
  public static void SharpmakeMain(Arguments arguments)
  {
    // First parse the commandline arguments that are passed in to sharpmake.
    rex.CmdLineArguments Arguments = new rex.CmdLineArguments();
    CommandLine.ExecuteOnObject(Arguments);

    // Initialize the globals, they get used all over the place
    // so best to initialize them as early as possible
    Globals.Init();

    // Load the config file so we can load the generate settings afterwards
    Dictionary<string, ConfigSetting> config = LoadConfigFile();

    // Initialize the generation settings and sharpmake.
    InitializeGenerationSettings(config);
    InitializeSharpmake();

    // Specify the solution that needs to get generate.
    // We only have one, so pass in the solution of the Rex Engine
    arguments.Generate<rex.MainSolution>();

    // Add the post generation events.
    // Our scripts need to be setup before can run those steps
    // That's why we do it post generation.
    Builder.Instance.EventPostGeneration += PostGenerationEvent;
  }

  // Load the specified config file from disk
  // Returns a dictionary to each item in the config file.
  private static Dictionary<string, ConfigSetting> LoadConfigFile()
  {
    string json = File.ReadAllText(ProjectGen.Settings.ConfigFileDir);
    return JsonSerializer.Deserialize<Dictionary<string, ConfigSetting>>(json);
  }

  // Perform post generation steps here.
  // You can assume that the generation of all projects in the solution are done.
  // Therefore you can use the dependency graph
  private static void PostGenerationEvent(List<Project> projects, List<Solution> solutions)
  {
    GenerateCompilerDatabases();
    CodeGeneration.Generate();
  }

  // Compiler database are not generated through Sharpmake directly.
  // We have the option to do so, but we chose to use Ninja to generate them
  // This way we only need to maintain our ninja files and we get the copmiler dbs for free
  private static void GenerateCompilerDatabases()
  {
    Console.WriteLine("Generating compiler databases");

    System.Diagnostics.ProcessStartInfo start_info = new System.Diagnostics.ProcessStartInfo();
    start_info.FileName = "cmd.exe";
    start_info.RedirectStandardOutput = true;
    start_info.RedirectStandardError = true;
    start_info.UseShellExecute = false;

    foreach (ProjectGen.GenerateCompilerDBCommand cmd in ProjectGen.Settings.GenerateCompilerDBCommands)
    {
      // An example command would be: cmd.exe /C ninja.exe -f my_ninja_file.ninja compdb_rex_debug_clang --quiet > compiler_commands.json
      start_info.Arguments = $"/C {KitsRootPaths.GetNinjaPath()} -f {cmd.NinjaFile} {cmd.CompilerDBBuildCommand} --quiet > {cmd.OutputPath}";

      System.Diagnostics.Process process = new System.Diagnostics.Process();
      process.StartInfo = start_info;

      process.Start();
      process.WaitForExit();
    }
  }

  // Pass in the paths to the toolchain tools to sharpmake and specify the windows target version
  private static void InitializeSharpmake()
  {
    InitializeToolChain();

    // Initialize Visual Studio settings
    KitsRootPaths.SetUseKitsRootForDevEnv(DevEnv.vs2019, KitsRootEnum.KitsRoot10, Options.Vc.General.WindowsTargetPlatformVersion.v10_0_19041_0);
  }

  // Initialize the graphics API based on the config
  // If no Graphics API is specified, we base it on the OS this script is running on
  private static void InitializeGraphicsAPI(Dictionary<string, ConfigSetting> config)
  {
    if (!Enum.TryParse(config["graphics-api"].Value.GetString(), ignoreCase: true, out ProjectGen.Settings.GraphicsAPI))
    {
      OperatingSystem os = Environment.OSVersion;
      switch (os.Platform)
      {
        case PlatformID.Win32NT:
        case PlatformID.Xbox:
          ProjectGen.Settings.GraphicsAPI = ProjectGen.GraphicsAPI.DirectX12;
          break;
        case PlatformID.Unix:
        case PlatformID.MacOSX:
          ProjectGen.Settings.GraphicsAPI = ProjectGen.GraphicsAPI.OpenGL;
          break;
        default:
          Console.WriteLine("[WARNING] Could not determine OS, reverting graphics API to OpenGL");
          ProjectGen.Settings.GraphicsAPI = ProjectGen.GraphicsAPI.OpenGL;
          break;
      }
    }

    Console.WriteLine($"Using Graphics API: {ProjectGen.Settings.GraphicsAPI}");
  }

  // Initialize the generation settings based on the config that's loaded from disk
  private static void InitializeGenerationSettings(Dictionary<string, ConfigSetting> config)
  {
    InitializeGraphicsAPI(config);

    ProjectGen.Settings.ClangTidyRegex = config["clang-tidy-regex"].Value.GetString();
    ProjectGen.Settings.PerformAllClangTidyChecks = config["perform-all-clang-tidy-checks"].Value.GetBoolean();
    ProjectGen.Settings.NoClangTools = config["no-clang-tools"].Value.GetBoolean();
    ProjectGen.Settings.IntermediateDir = config["intermediate-dir"].Value.GetString();
    ProjectGen.Settings.UnitTestsEnabled = config["enable-unit-tests"].Value.GetBoolean();
    ProjectGen.Settings.CoverageEnabled = config["enable-code-coverage"].Value.GetBoolean();
    ProjectGen.Settings.AsanEnabled = config["enable-address-sanitizer"].Value.GetBoolean();
    ProjectGen.Settings.UbsanEnabled = config["enable-ub-sanitizer"].Value.GetBoolean();
    ProjectGen.Settings.FuzzyTestingEnabled = config["enable-fuzzy-testing"].Value.GetBoolean();
    ProjectGen.Settings.AutoTestsEnabled = config["enable-auto-tests"].Value.GetBoolean();
    Enum.TryParse(config["IDE"].Value.GetString(), out ProjectGen.Settings.IDE);
    ProjectGen.Settings.DisableClangTidyForThirdParty = config["disable-clang-tidy-for-thirdparty"].Value.GetBoolean();

  }

  // Pass the toolchain paths over to sharpmake so it can use it for generation.
  private static void InitializeToolChain()
  {
    string tools_json_path = Path.Combine(Globals.ToolsRoot, "tool_paths.json");
    string json_blob = File.ReadAllText(tools_json_path);
    Dictionary<string, string> paths = JsonSerializer.Deserialize<Dictionary<string, string>>(json_blob);

    KitsRootPaths.SetCompilerPaths(Compiler.MSVC, paths["msvc_compiler_path"], paths["msvc_linker_path"], paths["msvc_archiver_path"], "");
    KitsRootPaths.SetCompilerPaths(Compiler.Clang, paths["clang++_compiler_path"], paths["clang_linker_path"], paths["clang_archiver_path"], paths["clang_ranlib_path"], paths["clang_compiler_path"]);
    KitsRootPaths.SetNinjaPath(paths["ninja_path"]);
  }
}