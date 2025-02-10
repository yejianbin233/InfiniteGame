// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Modules/ModuleManager.h"

class FIGGameplayTagExtendModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};


namespace IGGameplayTags
{
	IGGAMEPLAYTAGEXTEND_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	IGGAMEPLAYTAGEXTEND_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_LAYER_GAME);
	IGGAMEPLAYTAGEXTEND_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_LAYER_GAMEMENU);
	IGGAMEPLAYTAGEXTEND_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_LAYER_MENU);
	IGGAMEPLAYTAGEXTEND_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_LAYER_MODAL);
}