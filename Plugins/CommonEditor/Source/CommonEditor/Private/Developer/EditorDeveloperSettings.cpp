// Fill out your copyright notice in the Description page of Project Settings.


#include "Developer/EditorDeveloperSettings.h"


#if WITH_EDITOR
void UEditorDeveloperSettings::ApplySettings()
{
	// TODO
}

void UEditorDeveloperSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ApplySettings();
}

void UEditorDeveloperSettings::PostReloadConfig(class FProperty* PropertyThatWasLoaded)
{
	Super::PostReloadConfig(PropertyThatWasLoaded);
	ApplySettings();
}

void UEditorDeveloperSettings::PostInitProperties()
{
	Super::PostInitProperties();
	ApplySettings();
}


#endif
