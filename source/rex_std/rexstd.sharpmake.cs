using Sharpmake;
using System.IO;

[Generate]
public class RexStd : BasicCPPProject
{
  public RexStd() : base()
  {
    // The name of the project in Visual Studio. The default is the name of
    // the class, but you usually want to override that.
    Name = GenerateName("RexStd");
    GenerateTargets();

    // The directory that contains the source code we want to build is the
    // same as this one. This string essentially means "the directory of
    // the script you're reading right now."
    string ThisFileFolder = Path.GetDirectoryName(Utils.CurrentFile());
    SourceRootPath = ThisFileFolder;
  }

  protected override void SetupOutputType(RexConfiguration conf, RexTarget target)
  {
    conf.Output = Configuration.OutputType.Lib;
  }

  protected override void SetupCompilerRules(RexConfiguration conf, RexTarget target)
  {
    base.SetupCompilerRules(conf, target);

    switch (target.Compiler)
    {
      case Compiler.MSVC:
        conf.add_public_define("RSL_COMPILER_MSVC");
        break;
      case Compiler.Clang:
        conf.add_public_define("RSL_COMPILER_CLANG");
        break;
      case Compiler.GCC:
        conf.add_public_define("RSL_COMPILER_GCC");
        break;
      default:
        break;
    }
  }

  protected override void SetupConfigRules(RexConfiguration conf, RexTarget target)
  {
    base.SetupConfigRules(conf, target);

    switch (target.Config)
    {
      case Config.debug:
      case Config.debug_opt:
        conf.add_public_define("RSL_ENABLE_ASSERTS");
        break;
      case Config.release:
        break;
      case Config.coverage:
        ClangToolsEnabled = false;
        break;
    }
  }

  protected override void SetupPlatformRules(RexConfiguration conf, RexTarget target)
  {
    base.SetupPlatformRules(conf, target);

    switch (conf.Platform)
    {
      case Platform.win32:
        conf.add_public_define("RSL_PLATFORM_X86");
        conf.add_public_define("RSL_PLATFORM_WINDOWS");
        break;
      case Platform.win64:
        conf.add_public_define("RSL_PLATFORM_X64");
        conf.add_public_define("RSL_PLATFORM_WINDOWS");
        break;
      default:
        break;
    }

    conf.LibraryFiles.Add("Dbghelp.lib");
  }
}