// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "CommonGameEngine.generated.h"

/**
 * 
 */
UCLASS()
class COMMONGAME_API UCommonGameEngine : public UGameEngine
{
	GENERATED_BODY()

public:

	UCommonGameEngine(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Init(IEngineLoop* InEngineLoop) override;
};
