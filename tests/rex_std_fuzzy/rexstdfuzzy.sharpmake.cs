using Sharpmake;
using System.IO;

[Generate]
public class RexStdFuzzy : TestProject
{
  public RexStdFuzzy() : base()
  {
    Name = GenerateName("RexStdFuzzy");
    GenerateTargets();

    string ThisFileFolder = Path.GetDirectoryName(Utils.CurrentFile());
    SourceRootPath = ThisFileFolder;

    ProjectType = ProjectGen.TestProjectType.Fuzzy;
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