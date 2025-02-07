// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonGameEngine.h"

UCommonGameEngine::UCommonGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCommonGameEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);
}
