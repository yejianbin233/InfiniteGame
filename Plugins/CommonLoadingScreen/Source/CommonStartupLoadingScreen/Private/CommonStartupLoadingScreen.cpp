// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonCustomSplashScreen.h"
#include "CommonPreEarlyLoadingScreen.h"
#include "CommonPreLoadScreen.h"
#include "Misc/App.h"
#include "Modules/ModuleManager.h"
#include "PreLoadScreenManager.h"
#include "ScreenStyle.h"

#define LOCTEXT_NAMESPACE "FCommonLoadingScreenModule"

class FCommonStartupLoadingScreenModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	bool IsGameModule() const override;

private:
	void OnPreLoadScreenManagerCleanUp();

	TSharedPtr<FCommonCustomSplashScreen> CustomSplashScreen;
	TSharedPtr<FCommonPreEarlyLoadingScreen> PreEarlyLoadingScreen;
	TSharedPtr<FCommonPreLoadScreen> PreLoadingScreen;
};


void FCommonStartupLoadingScreenModule::StartupModule()
{
	// 初始化图片资产
	FEarlyStartupScreenStyle::Initialize();

	// No need to load these assets on dedicated servers.
	// Still want to load them in commandlets so cook catches them
	if (!IsRunningDedicatedServer())
	{
		PreLoadingScreen = MakeShared<FCommonPreLoadScreen>();
		PreLoadingScreen->Init();

		CustomSplashScreen = MakeShared<FCommonCustomSplashScreen>();
		CustomSplashScreen->Init();

		PreEarlyLoadingScreen = MakeShared<FCommonPreEarlyLoadingScreen>();
		PreEarlyLoadingScreen->Init();

		if (!GIsEditor && FApp::CanEverRender() && FPreLoadScreenManager::Get())
		{
			FPreLoadScreenManager::Get()->RegisterPreLoadScreen(CustomSplashScreen);
			FPreLoadScreenManager::Get()->RegisterPreLoadScreen(PreEarlyLoadingScreen);
			FPreLoadScreenManager::Get()->RegisterPreLoadScreen(PreLoadingScreen);
			FPreLoadScreenManager::Get()->OnPreLoadScreenManagerCleanUp.AddRaw(this, &FCommonStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp);
		}
	}
}

void FCommonStartupLoadingScreenModule::OnPreLoadScreenManagerCleanUp()
{
	//Once the PreLoadScreenManager is cleaning up, we can get rid of all our resources too
	CustomSplashScreen.Reset();
	PreEarlyLoadingScreen.Reset();
	PreLoadingScreen.Reset();
	ShutdownModule();
}

void FCommonStartupLoadingScreenModule::ShutdownModule()
{
	// 注销图片资产
	FEarlyStartupScreenStyle::Shutdown();
}

bool FCommonStartupLoadingScreenModule::IsGameModule() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonStartupLoadingScreenModule, CommonStartupLoadingScreen)
