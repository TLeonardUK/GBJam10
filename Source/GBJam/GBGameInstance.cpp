// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBGameInstance.h"
#include "HAL/IConsoleManager.h"

void UGBGameInstance::Init()
{
    Super::Init();

//    IConsoleVariable* CVar_UpscaleQuality = IConsoleManager::Get().FindConsoleVariable(TEXT("r.UpsampleQuality"));
//    IConsoleVariable* CVar_ScreenPercentage = IConsoleManager::Get().FindConsoleVariable(TEXT("r.ScreenPercentage"));
//    IConsoleVariable* CVar_ResolutionQuality = IConsoleManager::Get().FindConsoleVariable(TEXT("sg.ResolutionQuality"));

//    CVar_UpscaleQuality->Set(0, ECVF_SetByCode);
//    CVar_ScreenPercentage->Set(25, ECVF_SetByCode);
//    CVar_ResolutionQuality->Set(100, ECVF_SetByCode);
}
