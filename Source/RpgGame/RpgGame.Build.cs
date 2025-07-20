// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RpgGame : ModuleRules
{
	public RpgGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
			"UMG",
			"CommonUI"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"RpgGame",
			"RpgGame/Variant_Platforming",
			"RpgGame/Variant_Combat",
			"RpgGame/Variant_Combat/AI",
			"RpgGame/Variant_SideScrolling",
			"RpgGame/Variant_SideScrolling/Gameplay",
			"RpgGame/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
