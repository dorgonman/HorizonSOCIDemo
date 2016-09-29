// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System;
using System.IO;

public class HorizonSOCIDemo : ModuleRules
{
	public HorizonSOCIDemo(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "soci_core", "soci_sqlite3" });
       // PrivateDependencyModuleNames.AddRange(new string[] { "sqlite3Static" });
        System.Diagnostics.Debug.WriteLine("===== ModuleLibSqlite3PublicIncludePath:" + ModuleLibSqlite3PublicIncludePath);
        PublicIncludePaths.AddRange(
          new string[] {
                ModuleLibSociPublicIncludePath,
                ModuleLibSqlite3PublicIncludePath,

              // ... add public include paths required here ...
          }
          );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        bEnableExceptions = true;
        // eventually needed as well
        UEBuildConfiguration.bForceEnableExceptions = true;

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
    private string ModuleRootPath
    {
        get
        {
            string ModuleCSFilename = UnrealBuildTool.RulesCompiler.GetFileNameFromType(GetType());
            string ModuleCSFileDirectory = Path.GetDirectoryName(ModuleCSFilename);
            return Path.Combine(ModuleCSFileDirectory);
        }
    }

    private string ModuleLibSociPublicIncludePath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleRootPath, "..", "..", "Plugins", "HorizonSOCIPlugin", "Source", "ThirdParty", "LibSoci", "soci", "include"));
        }
    }



    private string ModuleLibSqlite3PublicIncludePath
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleRootPath, "..", "..", "Plugins", "HorizonSOCIPlugin", "Source", "ThirdParty", "LibSqlite3", "sqlite3", "src"));
        }
    }
}
