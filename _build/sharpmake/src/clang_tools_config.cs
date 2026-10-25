using System.Collections.Generic;
using System.IO;

// The clang tools project is used by the post build events
// They read the header filters and only enable clang-tidy
// for files who match the regex
class ClangToolsConfig
{
  public string Name {get; set;} // The name of the project
  public string SrcRoot {get; set; } // The source root directory
  public string CompilerDBDirectory {get; set; } // The directory of the compiler db
  public bool PerformAllChecks {get; set; } // Enable all checks, not just the auto fixes
  public string ClangTidyRegex { get; set; } // Regex to match files used by clang-tidy
  public List<string> HeaderFilters { get; set; } // The header regex values to be used for clang tools
}