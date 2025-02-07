// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#include "CommonEditorEngine.generated.h"

/**
 * 
 */
UCLASS()
class COMMONEDITOR_API UCommonEditorEngine : public UUnrealEdEngine
{
	GENERATED_BODY()

public:
	UCommonEditorEngine(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void Init(IEngineLoop* InEngineLoop) override;

	virtual void Start() override;

	virtual void Tick(float DeltaSeconds, bool bIdleMode) override;

	virtual FGameInstancePIEResult PreCreatePIEInstances(const bool bAnyBlueprintErrors, const bool bStartInSpectatorMode, const float PIEStartTime, const bool bSupportsOnlinePIE, int32& InNumOnlinePIEInstances) override;

private:
	void FirstTickSetup();
	
	bool bFirstTickSetup = false;
};
