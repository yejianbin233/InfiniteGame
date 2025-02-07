// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonEditor.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "FCommonEditorModule"

DEFINE_LOG_CATEGORY(LogCommonEditor);

void FCommonEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogCommonEditor, Display, TEXT("FCommonEditorModule Startup"));

	if (!IsRunningGame())
	{
		// 注册菜单
		RegisterCommonEditorMenus();

		// 注册通知事件
		FEditorDelegates::BeginPIE.AddRaw(this, &FCommonEditorModule::OnBeginPIE);
		FEditorDelegates::EndPIE.AddRaw(this, &FCommonEditorModule::OnEndPIE);
	}
}

void FCommonEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// 取消监听
	FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);

	// 取消菜单拓展
	if (UObjectInitialized() && ToolMenusHandle.IsValid())
	{
		UToolMenus::UnRegisterStartupCallback(ToolMenusHandle);
	}
	
	UE_LOG(LogCommonEditor, Display, TEXT("FCommonEditorModule Shutdown"));
}

void FCommonEditorModule::RegisterCommonEditorMenus()
{
	if (FSlateApplication::IsInitialized())
	{
		ToolMenusHandle = UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCommonEditorModule::RegisterEditorMenus));
	}
}

void FCommonEditorModule::OnBeginPIE(bool bIsSimulating)
{
	// 显示通知
	FNotificationInfo Info(LOCTEXT("BeginPIE", "BeginPIE"));
	Info.ExpireDuration = 2.0f;
	FSlateNotificationManager::Get().AddNotification(Info);
}

void FCommonEditorModule::OnEndPIE(bool bIsSimulating)
{
	// 显示通知
	FNotificationInfo Info(LOCTEXT("EndPIE", "EndPIE"));
	Info.ExpireDuration = 2.0f;
	FSlateNotificationManager::Get().AddNotification(Info);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonEditorModule, CommonEditor)