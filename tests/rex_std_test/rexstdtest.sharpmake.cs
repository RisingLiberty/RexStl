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

  protected override void SetupLibDependencies(RexConfiguration conf, RexTarget target)
  {
    base.SetupLibDependencies(conf, target);

    conf.AddPublicDependency<RexStd>(target, DependencySetting.Default | DependencySetting.IncludeHeadersForClangtools);
  }

  protected override void SetupConfigSettings(RexConfiguration conf, RexTarget target)
  {
    base.SetupConfigSettings(conf, target);

    conf.Options.Remove(Options.Vc.Compiler.JumboBuild.Enable);
  }
}