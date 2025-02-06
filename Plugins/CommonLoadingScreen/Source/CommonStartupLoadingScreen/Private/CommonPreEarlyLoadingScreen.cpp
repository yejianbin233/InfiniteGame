// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonPreEarlyLoadingScreen.h"

#include "SCommonPreEarlyLoadingScreenWidget.h"
#include "Misc/App.h"
#include "SCommonPreLoadingScreenWidget.h"

#define LOCTEXT_NAMESPACE "CommonPreEarlyLoadingScreen"

void FCommonPreEarlyLoadingScreen::Init()
{
	if (!GIsEditor && FApp::CanEverRender())
	{
		UE_LOG(LogTemp, Warning, TEXT("1[FCommonPreEarlyLoadingScreen]..."));
		EngineLoadingWidget = SNew(SCommonPreEarlyLoadingScreenWidget);
	}
}

void FCommonPreEarlyLoadingScreen::CleanUp()
{
	FPreLoadScreenBase::CleanUp();
	if (EngineLoadingWidget)
	{
		EngineLoadingWidget.Reset();
	}
}

void FCommonPreEarlyLoadingScreen::Tick(float DeltaTime)
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
		// EngineLoadingWidget->UpdateBorderColor(Colors[Index]);
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

bool FCommonPreEarlyLoadingScreen::IsDone() const
{
	return IsDoneCounter.GetValue() != 0;
}

#undef LOCTEXT_NAMESPACE
