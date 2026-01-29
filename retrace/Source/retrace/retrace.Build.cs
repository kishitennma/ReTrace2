using UnrealBuildTool;

public class retrace : ModuleRules
{
    public retrace(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "CinematicCamera",
            "GameplayCameras",
            "UMG",
            "Slate",
            "SlateCore",
            "Niagara",
            "Chaos",
            "ChaosSolverEngine",
            "GeometryCollectionEngine"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
