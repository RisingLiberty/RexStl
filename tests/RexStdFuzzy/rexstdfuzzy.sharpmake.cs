using Sharpmake;
using System.IO;

[Generate]
public class RexStdFuzzy : TestProject
{
  public RexStdFuzzy() : base()
  {
    Name = GenerateName("RexStdFuzzy");
    GenerateTargets();

    SourceRootPath = Path.Combine(Globals.Root, "tests", "RexStdFuzzy");
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.Output = Configuration.OutputType.Exe;

    conf.Options.Remove(Options.Vc.Compiler.JumboBuild.Enable);

    conf.add_dependency<RexStd>(target);
  }
}