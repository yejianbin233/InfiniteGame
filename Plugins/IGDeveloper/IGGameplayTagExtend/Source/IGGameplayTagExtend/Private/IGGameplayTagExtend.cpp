// Copyright Epic Games, Inc. All Rights Reserved.

#include "IGGameplayTagExtend.h"

#define LOCTEXT_NAMESPACE "FIGGameplayTagExtendModule"

void FIGGameplayTagExtendModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FIGGameplayTagExtendModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FIGGameplayTagExtendModule, IGGameplayTagExtend)

namespace IGGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_LAYER_GAME, "UI.Layer.Game", "Game");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_LAYER_GAMEMENU, "UI.Layer.GameMenu", "GameMenu");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_LAYER_MENU, "UI.Layer.Menu", "Menu");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(UI_LAYER_MODAL, "UI.Layer.Modal", "Modal");
}