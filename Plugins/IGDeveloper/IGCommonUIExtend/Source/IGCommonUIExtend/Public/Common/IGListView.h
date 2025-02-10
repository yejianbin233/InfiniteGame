// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "IGListView.generated.h"

class UIGWidgetFactory;
/**
 * 
 */
UCLASS(meta = (DisableNativeTick))
class IGCOMMONUIEXTEND_API UIGListView : public UCommonListView
{
	GENERATED_BODY()

public:
	UIGListView(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR

	/*
	 * 在 控件蓝图 编译结束时调用。允许 UMG 元素评估其默认状态并确定它们是否可接受。要触发编译失败，请在日志中添加错误。警告和注释将可见，但不会导致编译失败。
	 */
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& InCompileLog) const override;
#endif

protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	//virtual bool OnIsSelectableOrNavigableInternal(UObject* SelectedItem) override;

protected:
	UPROPERTY(EditAnywhere, Instanced, Category="Entry Creation")
	TArray<TObjectPtr<UIGWidgetFactory>> FactoryRules;
};
