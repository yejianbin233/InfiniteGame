// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCommonEditor, Log, All);

class FCommonEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	void RegisterCommonEditorMenus();
	void RegisterEditorMenus();

	void OnBeginPIE(bool bIsSimulating);
	void OnEndPIE(bool bIsSimulating);
private:
	FDelegateHandle ToolMenusHandle;
};
