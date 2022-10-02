// Copyright 2022 Tim Leonard. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GBJamTarget : TargetRules
{
	public GBJamTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("GBJam");
	}
}
