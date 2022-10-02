// Copyright 2022 Tim Leonard. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GBJamEditorTarget : TargetRules
{
	public GBJamEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("GBJam");
	}
}
