﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// these are the values that come the json file
public class EnumGenerationConfig
{
  public string ClassName { get; set; }
  public List<string> Values { get; set; }
  public string Filepath { get; set; }
}

// this is the object we use
public class EnumGenerationSettings
{
  public string ClassName = "";
  public string Filepath = "";
  public Dictionary<string, List<string>> ProjectToEnumValues = new Dictionary<string, List<string>>();
}

public class GenerateSettings
{
  static public bool EnableVisualStudio = false;
  static public bool NoClangTools = false;
  static public bool PerformAllChecks = false;
  static public string IntermediateDir = "";

  // Test flags
  static public bool EnableDefaultGeneration = true;
  static public bool GenerateUnitTests = false;
  static public bool CoverageEnabled = false;
  static public bool AddressSanitizerEnabled = false;
  static public bool UndefinedBehaviorSanitizerEnabled = false;
  static public bool GenerateFuzzyTests = false;


  static public string ClangTidyRegex { get; set; }

  static public Dictionary<string, EnumGenerationSettings> EnumsToAutoGenerate = new Dictionary<string, EnumGenerationSettings>();

  static public List<System.Diagnostics.Process> GenerateCompilerDBProcesses = new List<System.Diagnostics.Process>();
}
