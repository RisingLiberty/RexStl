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
    GenerateCompilerDB = true;
    GenerateTargets();

    // The directory that contains the source code we want to build is the
    // same as this one. This string essentially means "the directory of
    // the script you're reading right now."
    string ThisFileFolder = Path.GetDirectoryName(Utils.CurrentFile());
    SourceRootPath = ThisFileFolder;
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

    conf.LibraryFiles.Add("Dbghelp.lib");
  }
}