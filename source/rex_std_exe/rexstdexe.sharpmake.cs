using Sharpmake;
using System.IO;

[Generate]
public class RexStdExe : BasicCPPProject
{
  public RexStdExe() : base()
  {
    Name = GenerateName("RexStdExe");
    GenerateTargets();

    string ThisFileFolder = Path.GetDirectoryName(Utils.CurrentFile());
    SourceRootPath = ThisFileFolder;
  }

  public override void Configure(RexConfiguration conf, RexTarget target)
  {
    base.Configure(conf, target);

    conf.Output = Configuration.OutputType.Exe;

    conf.AddPublicDependency<RexStd>(target, DependencySetting.Default | DependencySetting.IncludeHeadersForClangtools);
  }
}