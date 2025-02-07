// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "EditorDeveloperSettings.generated.h"

/**
 * Developer settings / editor cheats
 */
UCLASS(Config=EditorDeveloperSettings, defaultconfig, meta=(DisplayName="Editor Developer Settings"))
class COMMONEDITOR_API UEditorDeveloperSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()


public:

#if WITH_EDITORONLY_DATA

	// 通过设置，可以打开常用的 Map
	UPROPERTY(Config, EditAnywhere, Category = Maps, BlueprintReadOnly, meta=(AllowedClasses = "/Script/Engine.World"))
	TArray<FSoftObjectPath> CommonEditorMaps;
	
#endif

private:
#if WITH_EDITOR
	void ApplySettings();
#endif
	
#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostReloadConfig(class FProperty* PropertyThatWasLoaded) override;
	virtual void PostInitProperties() override;

#endif
};
