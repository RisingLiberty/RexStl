using Sharpmake;
using System.IO;

[Generate]
public class RexStdExe : BasicCPPProject
{
  public RexStdExe() : base()
  {
    Name = GenerateName("RexStdExe");
    GenerateTargets();

    SourceRootPath = Path.Combine(Globals.SourceRoot, "rex_std_exe");
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.Output = Configuration.OutputType.Exe;

    conf.add_dependency<RexStd>(target);
  }
}