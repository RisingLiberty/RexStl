using Sharpmake;
using System.IO;

[Generate]
public class RexStdTest : TestProject
{
  public RexStdTest() : base()
  {
    Name = GenerateName("RexStdTest");
    GenerateTargets();

    string ThisFileFolder = Path.GetDirectoryName(Utils.CurrentFile());
    SourceRootPath = ThisFileFolder;
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.Output = Configuration.OutputType.Exe;

    conf.Options.Remove(Options.Vc.Compiler.JumboBuild.Enable);

    conf.add_dependency<RexStd>(target);
  }
}