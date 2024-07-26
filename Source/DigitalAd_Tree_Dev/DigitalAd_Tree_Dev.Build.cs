// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DigitalAd_Tree_Dev : ModuleRules
{
	public DigitalAd_Tree_Dev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
		"Core",
		"CoreUObject",
		"Engine",
		"InputCore",
        "UnrealEd",           // For Editor Utilities
        "Blutility",          // For Blueprint Utility Widgets
        "UMG",                // For UMG (Unreal Motion Graphics)
        "UMGEditor",          // For UMG Editor functionalities
        "Slate",
		"DesktopPlatform",              // For Slate UI
        "SlateCore",          // For Slate UI
        "EditorStyle",        // For Editor styling
        "PropertyEditor",     // For Property Editor
        "ToolMenus"           // For custom editor menus
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
