// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EscapeRoom : ModuleRules
{
	public EscapeRoom(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore", "UMG", "MediaAssets" });
	}
}
