// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "IGTabListWidgetBase.generated.h"


USTRUCT(BlueprintType)
struct FTabDescriptor
{
	GENERATED_BODY()

public:
	FTabDescriptor()
	: bHidden(false)
	, CreatedTabContentWidget(nullptr)
	{ }

	// Tab 的 Id 标识
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName TabId;

	// Tab 的内容文本
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TabText;

	// Tab 的图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush IconBrush;

	// 是否隐藏
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHidden;

	// Tab 的按钮类型
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UCommonButtonBase> TabButtonType;

	// Tab 的 内容类型
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UCommonUserWidget> TabContentType;

	// Tab 的 内容控件
	UPROPERTY(Transient)
	TObjectPtr<UWidget> CreatedTabContentWidget;
};

UINTERFACE(BlueprintType)
class UTabButtonInterface : public UInterface
{
	GENERATED_BODY()
};

class ITabButtonInterface
{
	GENERATED_BODY()

public:

	// 设置 Tab 的信息
	UFUNCTION(BlueprintNativeEvent, Category = "Tab Button")
	void SetTabLabelInfo(const FTabDescriptor& TabDescriptor);
};


/**
 * 扩展 UCommonTabListWidgetBase Tab 列表控件
 */
UCLASS(Blueprintable, BlueprintType, Abstract, meta=(DisableNativeTick))
class IGCOMMONUIEXTEND_API UIGTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
	
public:

	// 获取预注册的 Tab 信息
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	bool GetPreregisteredTabInfo(const FName TabNameId, FTabDescriptor& OutTabInfo);

	/** Helper method to get at all the preregistered tab infos
	 * 获取所有预注册标签页信息的 Helper 方法
	 */
	const TArray<FTabDescriptor>& GetAllPreregisteredTabInfos() { return PreregisteredTabInfoArray; }

	/* Toggles whether or not a specified tab is hidden, can only be called before the switcher is associated
	 * 切换指定的选项卡是否隐藏，只能在关联切换器之前调用
	 */
	UFUNCTION(BlueprintCallable, Category = "Tab List")
	void SetTabHiddenState(FName TabNameId, bool bHidden);

	// 注册动态 Tab
	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool RegisterDynamicTab(const FTabDescriptor& TabDescriptor);

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool IsFirstTabActive() const;

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool IsLastTabActive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	bool IsTabVisible(FName TabId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	int32 GetVisibleTabCount();

	/**
	 * Delegate broadcast when a new tab is created. Allows hook ups after creation.
	 * 创建新选项卡时代理广播。允许在创建后进行连接。
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabContentCreated, FName, TabId, UCommonUserWidget*, TabWidget);
	DECLARE_EVENT_TwoParams(ULyraTabListWidgetBase, FOnTabContentCreatedNative, FName /* TabId */, UCommonUserWidget* /* TabWidget */);

	/** Broadcasts when a new tab is created. */
	UPROPERTY(BlueprintAssignable, Category = "Tab List")
	FOnTabContentCreated OnTabContentCreated;
	FOnTabContentCreatedNative OnTabContentCreatedNative;

protected:
	// UUserWidget interface
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget

	virtual void HandlePreLinkedSwitcherChanged() override;
	virtual void HandlePostLinkedSwitcherChanged() override;

	virtual void HandleTabCreation_Implementation(FName TabId, UCommonButtonBase* TabButton) override;

private:
	void SetupTabs();

	// 预注册 Tab 信息数组
	UPROPERTY(EditAnywhere, meta=(TitleProperty="TabId"))
	TArray<FTabDescriptor> PreregisteredTabInfoArray;
	
	/**
	 * Stores label info for tabs that have been registered at runtime but not yet created. 
	 * Elements are removed once they are created.
	 * 存储已在运行时注册但尚未创建的选项卡的标签信息，元素创建后将被删除。
	 */
	UPROPERTY()
	TMap<FName, FTabDescriptor> PendingTabLabelInfoMap;
	
};
