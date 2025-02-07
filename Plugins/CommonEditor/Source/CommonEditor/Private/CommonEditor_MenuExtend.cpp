

#include "CommonEditor.h"
#include "Developer/EditorDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "FCommonEditorModule"

#if WITH_EDITOR

static bool HasPlayWorld()
{
	return GEditor->PlayWorld != nullptr;
}

static bool HasNoPlayWorld()
{
	return !HasPlayWorld();
}



#pragma region CommonMapBrowseMenu

// 打开指定路径的 Map
static void OpenCommonMap_Clicked(const FString MapPath)
{
	if (ensure(MapPath.Len()))
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(MapPath);
	}
}

// 创建 Editor 菜单的下拉框控件
static TSharedRef<SWidget> GetCommonMapsDropdown()
{
	FMenuBuilder MenuBuilder(true, nullptr);

	for (const FSoftObjectPath& MapPath : GetDefault<UEditorDeveloperSettings>()->CommonEditorMaps)
	{
		if (!MapPath.IsValid())
		{
			continue;
		}

		const FText DisplayName = FText::FromString(MapPath.GetAssetName());
		MenuBuilder.AddMenuEntry(
			DisplayName,
			LOCTEXT("CommonPathDescription", "Opens this map in the editor"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateStatic(&OpenCommonMap_Clicked, MapPath.ToString()), // 点击后执行的逻辑
				FCanExecuteAction::CreateStatic(&HasNoPlayWorld), // 是否可执行的条件
				FIsActionChecked(),
				FIsActionButtonVisible::CreateStatic(&HasNoPlayWorld) // 是否可视的条件
			)
		);
	}

	return MenuBuilder.MakeWidget();
}

static bool CanShowCommonMaps()
{
	return HasNoPlayWorld() && !GetDefault<UEditorDeveloperSettings>()->CommonEditorMaps.IsEmpty();
}
#pragma endregion 





#pragma region RegisterEditorMenus

void FCommonEditorModule::RegisterEditorMenus()
{
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	FToolMenuSection& Section = Menu->AddSection("PlayGameExtensions", TAttribute<FText>(), FToolMenuInsert("Play", EToolMenuInsertType::After));

	// TODO 是否需要校验（Validaor）

	// 注册 Map 浏览菜单
	FToolMenuEntry CommonMapEntry = FToolMenuEntry::InitComboButton(
		"CommonMapOptions",
		FUIAction(
			FExecuteAction(),
			FCanExecuteAction::CreateStatic(&HasNoPlayWorld),
			FIsActionChecked(),
			FIsActionButtonVisible::CreateStatic(&CanShowCommonMaps)),
		FOnGetContent::CreateStatic(&GetCommonMapsDropdown),
		LOCTEXT("CommonMaps_Label", "Common Maps"),
		LOCTEXT("CommonMaps_ToolTip", "Some commonly desired maps while using the editor"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Level")
	);
	CommonMapEntry.StyleNameOverride = "CalloutToolbar";
	Section.AddEntry(CommonMapEntry);
}

#pragma endregion

#endif

#undef LOCTEXT_NAMESPACE