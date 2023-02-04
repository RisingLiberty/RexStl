using Sharpmake;
using System.IO;

[Generate]
public class RexStdExtra : BasicCPPProject
{
  public RexStdExtra() : base()
  {
    // The name of the project in Visual Studio. The default is the name of
    // the class, but you usually want to override that.
    Name = GenerateName("RexStdExtra");
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

    if (target.Compiler == Compiler.Clang && conf.is_config_for_testing() == false)
    {
      conf.NinjaGenerateCompilerDB = true;
      string compdbPath = Path.Combine(conf.ProjectPath, "clang_tools", target.Compiler.ToString(), conf.Name);
      string postbuildCommandScript = Path.Combine(Globals.SourceRoot, $"post_build.py -p={Name} -comp={target.Compiler} -conf={conf.Name} -compdb={compdbPath} -srcroot={SourceRootPath}");
      conf.EventPostBuild.Add($"py {postbuildCommandScript}");
    }

    conf.add_dependency<RexStd>(target);
  }
}