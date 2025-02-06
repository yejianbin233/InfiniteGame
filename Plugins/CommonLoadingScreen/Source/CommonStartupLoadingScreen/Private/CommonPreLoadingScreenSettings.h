// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "UObject/SoftObjectPath.h"

#include "CommonPreLoadingScreenSettings.generated.h"

class UObject;

/**
 * Settings for a loading screen system.
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Common Pre Loading Screen"))
class UCommonPreLoadingScreenSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UCommonPreLoadingScreenSettings();

public:
	
	// The widget to load for the loading screen.
	UPROPERTY(config, EditAnywhere, Category=Display)
	FSoftObjectPath LoadingScreenTexture;
};

