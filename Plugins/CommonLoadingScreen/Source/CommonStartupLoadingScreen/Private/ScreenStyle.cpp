// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
TSharedPtr<FSlateStyleSet> FEarlyStartupScreenStyle::StyleSet = nullptr;
TSharedPtr<ISlateStyle> FEarlyStartupScreenStyle::Get()
{
	return StyleSet;
}

FName FEarlyStartupScreenStyle::GetStyleSetName()
{
	static const FName EarlyStartupScreenStyleName(TEXT("EarlyStartupScreenStyle"));
	return EarlyStartupScreenStyleName;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FEarlyStartupScreenStyle::Initialize()
{
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(
		IPluginManager::Get().FindPlugin(PreLoadingScreenBeforeData::PLUGIN_NAME.ToString())->GetBaseDir() / PreLoadingScreenBeforeData::RUNTIME_DEPENDENCIES_RELATIVE_PATH.ToString()
	);

	StyleSet->Set(
		PreLoadingScreenBeforeData::STYLEPROPERTYNAME_IMAGE,
		new IMAGE_BRUSH(PreLoadingScreenBeforeData::IMAGE_FILENAME.ToString(), PreLoadingScreenBeforeData::IMAGE_SIZE)
	);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FEarlyStartupScreenStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

#undef IMAGE_BRUSH
