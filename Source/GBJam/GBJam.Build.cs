// Copyright 2022 Tim Leonard. All Rights Reserved.

using UnrealBuildTool;

public class GBJam : ModuleRules
{
	public GBJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
