//*********************************************************************************
//
// This file was auto generated.
// Manual changes to this will be overwritten the next time the file is generated.
//

using Sharpmake;

[Fragment, System.Flags]
public enum Config
{
  assert = (1 << 0),
  debug = (1 << 1),
  debug_opt = (1 << 2),
  release = (1 << 3),
  tests = (1 << 4),
}

public class ConfigManager
{
  public static Config get_all_configs()
  {
    return Config.assert | Config.debug | Config.debug_opt | Config.release | Config.tests;
  }

  public static Optimization get_optimization_for_config(Config config)
  {
    switch (config)
    {
      case Config.assert: return Optimization.FullOptWithPdb;
      case Config.debug: return Optimization.NoOpt;
      case Config.debug_opt: return Optimization.FullOptWithPdb;
      case Config.release: return Optimization.FullOpt;
      case Config.tests: return Optimization.NoOpt;
    }
    return Optimization.FullOpt;
  }
}
