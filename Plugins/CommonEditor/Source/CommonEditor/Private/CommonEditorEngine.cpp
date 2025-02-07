// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonEditorEngine.h"

#include "Settings/ContentBrowserSettings.h"

UCommonEditorEngine::UCommonEditorEngine(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UCommonEditorEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);
}

void UCommonEditorEngine::Start()
{
	Super::Start();
}

void UCommonEditorEngine::Tick(float DeltaSeconds, bool bIdleMode)
{
	Super::Tick(DeltaSeconds, bIdleMode);
	
	FirstTickSetup();
}

FGameInstancePIEResult UCommonEditorEngine::PreCreatePIEInstances(const bool bAnyBlueprintErrors,
	const bool bStartInSpectatorMode, const float PIEStartTime, const bool bSupportsOnlinePIE,
	int32& InNumOnlinePIEInstances)
{

	// TODO 每次创建 PIE Instance 时触发
	
	FGameInstancePIEResult Result = Super::PreCreatePIEInstances(bAnyBlueprintErrors, bStartInSpectatorMode, PIEStartTime, bSupportsOnlinePIE,InNumOnlinePIEInstances);

	return Result;
}

void UCommonEditorEngine::FirstTickSetup()
{
	if (bFirstTickSetup)
	{
		return;
	}

	bFirstTickSetup = true;

	// 加载时强制显示插件内容。
	GetMutableDefault<UContentBrowserSettings>()->SetDisplayPluginFolders(true);
}
