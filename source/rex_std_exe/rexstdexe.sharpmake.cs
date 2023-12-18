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

  protected override void SetupOutputType(RexConfiguration conf, RexTarget target)
  {
    conf.Output = Configuration.OutputType.Exe;
  }

  protected override void SetupLibDependencies(RexConfiguration conf, RexTarget target)
  {
    base.SetupLibDependencies(conf, target);

    conf.AddPublicDependency<RexStd>(target, DependencySetting.Default | DependencySetting.IncludeHeadersForClangtools);
  }
}