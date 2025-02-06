// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonCustomSplashScreen.h"

#include "SCommonCustomSplashScreenWidget.h"
#include "Misc/App.h"

#define LOCTEXT_NAMESPACE "CommonCustomSplashScreen"

void FCommonCustomSplashScreen::Init()
{
	if (!GIsEditor && FApp::CanEverRender())
	{
		UE_LOG(LogTemp, Warning, TEXT("1[FCommonCustomSplashScreen]..."));
		EngineLoadingWidget = SNew(SCommonCustomSplashScreenWidget);
	}
}

void FCommonCustomSplashScreen::CleanUp()
{
	FPreLoadScreenBase::CleanUp();
	if (EngineLoadingWidget)
	{
		EngineLoadingWidget.Reset();
	}
}

void FCommonCustomSplashScreen::Tick(float DeltaTime)
{
	FPreLoadScreenBase::Tick(DeltaTime);

	if (EngineLoadingWidget)
	{
		TArray<FLinearColor> Colors;
		Colors.Add(FLinearColor::Red);
		Colors.Add(FLinearColor::Green);
		Colors.Add(FLinearColor::Blue);
		Colors.Add(FLinearColor::White);
		int Second = FPlatformTime::Seconds();
		int Index = Second % 3;
		EngineLoadingWidget->UpdateBorderColor(Colors[Index]);
	}
	if (DonableLastTime == 0)
	{
		DonableLastTime = FPlatformTime::Seconds();
	}

	if (IsEngineExitRequested() || (FPlatformTime::Seconds() - DonableLastTime) >= 10.0f)
	{
		IsDoneCounter.Set(1);
	}
}

bool FCommonCustomSplashScreen::IsDone() const
{
	return IsDoneCounter.GetValue() != 0;
}

#undef LOCTEXT_NAMESPACE
