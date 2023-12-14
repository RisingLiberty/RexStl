﻿using Sharpmake;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.Text.Json.Serialization;

// These are the classes used for automatic code generation
namespace CodeGen
{
  // An unknown type. This just holds a project to content dict
  public class UnknownTypeConfig
  {
    private Dictionary<string, List<string>> ProjectToContentMap = new Dictionary<string, List<string>>();

    public void AddContent(string projectName, List<string> content)
    {
      ProjectToContentMap.Add(projectName, content);
    }

    public Dictionary<string, List<string>> ProjectToContent
    {
      get { return ProjectToContentMap; }
    }
  }

  // A known type. This is the base class and holds all logic shared by auto generated types
  public abstract class TypeToGenerate
  {
    private Dictionary<string, List<string>> ProjectToContentMap = new Dictionary<string, List<string>>();
    private string Filepath = "";

    public string FilePath
    {
      get
      {
        return Filepath;
      }
    }
    protected Dictionary<string, List<string>> ProjectToContent 
    { 
      get 
      { 
        return ProjectToContentMap; 
      } 
    } 

    public TypeToGenerate(string filepath)
    {
      Filepath = System.IO.Path.Combine(Globals.SourceRoot, filepath);
    }

    // Add content to the internal dict
    public void AddContent(string projectName, List<string> content)
    {
      ProjectToContentMap.Add(projectName, content);
    }

    // Write out the type as a string to be passed to a file.
    // the string representation is written in C++.
    public abstract string AsString(string key);

    protected static void WriteCustomGenerationHeader(StringBuilder sb, string key)
    {
      sb.AppendLine("#pragma once");
      sb.AppendLine("");
      sb.AppendLine("// DON'T EDIT - This file is auto generated by sharpmake");
      sb.AppendLine($"// Generated from code generation key '{key}'");
      sb.AppendLine("// NOLINTBEGIN");
      sb.AppendLine("");
    }

    protected static void WriteBeginNamespace(StringBuilder sb, string namespaceName = "rex")
    {
      sb.AppendLine($"namespace {namespaceName}");
      sb.AppendLine($"{{");
    }

    protected static void WriteEndNamespace(StringBuilder sb, string namespaceName = "rex")
    {
      sb.AppendLine($"}} // namespace {namespaceName}");
      sb.AppendLine($"// NOLINTEND");
    }
  }

  // An auto generated enumeration
  public class EnumToGenerate : TypeToGenerate
  {
    private string ClassName = "";

    public EnumToGenerate(string className, string filepath, string projectName, List<string> content) : base(filepath)
    {
      ClassName = className;
      AddContent(projectName, content);
    }

    // Write out the type as a string to be passed to a file.
    // the string representation is written in C++.
    public override string AsString(string key)
    {
      StringBuilder sb = new StringBuilder();
      WriteCustomGenerationHeader(sb, key);
      WriteBeginNamespace(sb);

      sb.AppendLine($"  enum class {ClassName}");
      sb.AppendLine("  {");

      foreach (var project_vals in ProjectToContent)
      {
        sb.AppendLine($"    // {ClassName} values for {project_vals.Key}");

        foreach (string val in project_vals.Value)
        {
          sb.AppendLine($"    {val},");
        }
        sb.AppendLine(" ");
      }

      sb.AppendLine("  };");

      WriteEndNamespace(sb);

      return sb.ToString();
    }
  }

  // an auto generated array
  public class ArrayToGenerate : TypeToGenerate
  {
    private string ElementType = "";
    private string Name = "";
    private List<string> Includes = new List<string>();

    public ArrayToGenerate(string elementType, string name, string filepath, List<string> includes, string projectName, List<string> content) : base(filepath)
    {
      ElementType = elementType;
      Name = name;
      Includes = includes;
      AddContent(projectName, content);
    }

    // Write out the type as a string to be passed to a file.
    // the string representation is written in C++.
    public override string AsString(string key)
    {
      StringBuilder sb = new StringBuilder();

      WriteCustomGenerationHeader(sb, key);

      foreach (string include in Includes)
      {
        sb.AppendLine($"#include \"{include}\"");
      }

      sb.AppendLine($"#include \"rex_std/array.h\"");

      WriteBeginNamespace(sb);

      sb.AppendLine($"  inline rsl::array {Name} = ");
      sb.AppendLine("  {");

      foreach (var project_vals in ProjectToContent)
      {
        sb.AppendLine($"    // {ElementType} values for {project_vals.Key} - using code generation key: '{key}'");

        foreach (string val in project_vals.Value)
        {
          sb.AppendLine($"    {ElementType}{{ {val}, \"{project_vals.Key}\" }},");
        }
        sb.AppendLine(" ");
      }

      sb.AppendLine("  };");

      WriteEndNamespace(sb);
      return sb.ToString();
    }
  }
}

// These are the classes used for project generation
namespace ProjectGen
{
  // The graphics API to be used for rendering in the engine
  public enum GraphicsAPI
  {
    Unknown,
    OpenGL,
    DirectX12
  }

  // The IDE to be used for project generation
  public enum IDE
  {
    None,
    VisualStudio,
    VSCode
  }

  // A wrapper around the parameters to be used
  // for the command to generate the compiler db
  public class GenerateCompilerDBCommand
  {
    public string NinjaFile { get; set; }
    public string CompilerDBBuildCommand { get; set; }
    public string OutputPath { get; set; }

    public GenerateCompilerDBCommand(string ninjaFile, string compilerDBBuildCommand, string output)
    {
      NinjaFile = ninjaFile;
      CompilerDBBuildCommand = compilerDBBuildCommand;
      OutputPath = output;
    }
  }

  // Indicate what kind of test project this is
  // This is used in the test_projects.json file
  // And can then be used by CI
  public enum TestProjectType
  {
    UnitTest,
    AutoTest,
    Fuzzy,
    Undefined
  }

  public class TestProjectsFile
  {
    // Custom converter that we use to write the configurations
    public class ToJsonConverter : JsonConverter<Dictionary<TestProjectType, List<TestProjectSettings>>>
    {
      public override void Write(Utf8JsonWriter writer, Dictionary<TestProjectType, List<TestProjectSettings>> value, JsonSerializerOptions options)
      {
        // Configs are structured per compiler, per config
        writer.WriteStartObject(); // Write the opening brace

        foreach (var kvp in value)
        {
          TestProjectType type = kvp.Key;
          WriteProjectSettings(writer, options, type, kvp.Value);
        }

        writer.WriteEndObject(); // Write the closing brace
      }

      public override Dictionary<TestProjectType, List<TestProjectSettings>> Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
      {
        // Implement the Read method if needed
        throw new NotImplementedException();
      }

      private void WriteProjectSettings(Utf8JsonWriter writer, JsonSerializerOptions options, TestProjectType type, List<TestProjectSettings> settings)
      {
        writer.WritePropertyName(type.ToString()); // write test project type

        writer.WriteStartObject();  // Write the opening brace

        foreach (var setting in settings)
        {
          writer.WritePropertyName(setting.Name); // write project name
          JsonSerializer.Serialize(writer, setting, options); // write test project settings
        }

        writer.WriteEndObject(); // Write the closing brace
      }
    }

    public class TestProjectSettings
    {
      public string Name { get; }
      public string Root { get; }
      public string WorkingDir { get; }
      public List<string> TargetPaths { get; } = new List<string>();
      public List<string> CompilerDBPaths { get; } = new List<string>();

      public TestProjectSettings(Project project)
      {
        Name = project.Name;
        Root = project.SourceRootPath;
        WorkingDir = project.Configurations[0].VcxprojUserFile?.LocalDebuggerWorkingDirectory;

        foreach (Project.Configuration conf in project.Configurations)
        {
          var configTasks = PlatformRegistry.Get<Project.Configuration.IConfigurationTasks>(conf.Platform);

          // Making sure our prefix and extension are filled in or we get an error when resolving
          if (conf.TargetFilePlatformPrefix == null)
            conf.TargetFilePlatformPrefix = configTasks.GetOutputFileNamePrefix(conf.Output);
          if (conf.TargetFileFullExtension == null)
            conf.TargetFileFullExtension = configTasks.GetDefaultOutputFullExtension(conf.Output);

          Resolver resolver = new Resolver();
          resolver.SetParameter("conf", conf);
          resolver.SetParameter("project", this);
          string fullTargetPath = resolver.Resolve(System.IO.Path.Combine(conf.TargetPath, conf.TargetFileFullNameWithExtension));

          TargetPaths.Add(fullTargetPath);
          CompilerDBPaths.Add(Utils.GetCompilerDBOutputPath((RexConfiguration)conf));
        }

      }
    }

    [JsonConverter(typeof(TestProjectsFile.ToJsonConverter))]
    public Dictionary<TestProjectType, List<TestProjectSettings>> TypeSettings { get; set; } = new Dictionary<TestProjectType, List<TestProjectSettings>>();

    public TestProjectsFile()
    {
      // Nothing to implement
    }

    public void AddProject(TestProjectType type, Project project)
    {
      if (!TypeSettings.ContainsKey(type))
      {
        TypeSettings.Add(type, new List<TestProjectSettings>());
      }

      TypeSettings[type].Add(new TestProjectSettings(project));
    }
  }
    

  // 
  public class Settings
  {
    static public bool NoClangTools = false;                      // Are clang tools enabled?
    static public bool PerformAllClangTidyChecks = false;         // Perform all configured clang tidy checks, not just the warnings
    static public bool DisableClangTidyForThirdParty = true;      // Set to disable clang-tidy running on third party projects
    static public string IntermediateDir = "";                    // Set the directory name to be used under the build output directory for this generation
    static public string ConfigFileDir = "";                      // Filepath of the config file passed in to this instance of sharpmake

    // Flags for various different tests
    static public bool UnitTestsEnabled = false;                  // Enable generation of unit test projects
    static public bool CoverageEnabled = false;                   // Generate solution to test code coverage
    static public bool AsanEnabled = false;                       // Enable address sanitizer configuration
    static public bool UbsanEnabled = false;                      // Enable undefined behavior sanitizer configuration
    static public bool FuzzyTestingEnabled = false;               // Generate solution for fuzzy testing
    static public bool AutoTestsEnabled = false;                  // Generate solution for auto testing

    static public IDE IDE = IDE.VisualStudio;                     // Choose the IDE this sharpmake instance is generating for

    static public string ClangTidyRegex = "";                     // Regex of files to run clang-tidy on
    static public GraphicsAPI GraphicsAPI = GraphicsAPI.Unknown;  // The graphics API to be used by the engine
    static public bool UnityBuildsDisabled = false;               // Disable unity builds (aka jumbo builds or combi builds)

    static public List<GenerateCompilerDBCommand> GenerateCompilerDBCommands = new List<GenerateCompilerDBCommand>(); // List of command wrappers to generate compiler dbs for.
    
    static public TestProjectsFile TestProjectsFile = new TestProjectsFile();
  }
}