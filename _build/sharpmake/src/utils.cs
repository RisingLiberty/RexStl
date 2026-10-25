using System.Collections.Generic;
using System.IO;
using System.Linq;
using Sharpmake;
using static Sharpmake.Options.CSharp;

public class Utils
{
  // Get the current file that calls this function
  public static string CurrentFile([System.Runtime.CompilerServices.CallerFilePath] string fileName = "")
  {
    return fileName;
  }
  // Looks for a directory or file in the parent directory recursively
  // returns the directory where the directory or file is found
  public static string FindInParent(string startPath, string toFind)
  {
    string current_directory = startPath;

    while (Directory.GetDirectories(current_directory).ToList().FindIndex(x => Path.GetFileName(x) == toFind) == -1 && Directory.GetFiles(current_directory).ToList().FindIndex(x => Path.GetFileName(x) == toFind) == -1)
    {
      if (Directory.GetDirectoryRoot(current_directory) == current_directory)
      {
        return "";
      }
      current_directory = Directory.GetParent(current_directory).FullName;
    }

    return current_directory;
  }

  // Returns true if the given path falls under the root
  public static bool IsPartOfRoot(string root, string path)
  {
    string relativePath = Util.PathGetRelative(root, path);
    string[] pathTokens = relativePath.Split(Path.DirectorySeparatorChar);
    return pathTokens.Length == 0 || pathTokens[0] != "..";
  }

  // Always creates the file and writes the provided content to it
  // If the directory where the file is located doesn't exist, this directory is created first
  public static void SafeWriteFile(string filepath, string text)
  {
    if (!Directory.Exists(filepath))
    {
      Directory.CreateDirectory(Path.GetDirectoryName(filepath));
    }

    File.WriteAllText(filepath, text);
  }
}

public static class DictionaryExtensionMethods
{
  public static void AddRange<TKey, TValue>(this Dictionary<TKey, TValue> me, Dictionary<TKey, TValue> merge)
  {
    foreach (var item in merge)
    {
      me[item.Key] = item.Value;
    }
  }
}