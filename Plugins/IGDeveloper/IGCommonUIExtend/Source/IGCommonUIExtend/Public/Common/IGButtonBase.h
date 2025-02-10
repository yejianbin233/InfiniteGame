// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "IGButtonBase.generated.h"

/**
 * 扩展 UCommonButtonBase 按钮
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class IGCOMMONUIEXTEND_API UIGButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

#pragma region UUserWidgetOverride
protected:
	// UUserWidget interface
	virtual void NativePreConstruct() override;
	// End of UUserWidget interface

	// UCommonButtonBase interface
	virtual void UpdateInputActionWidget() override;
	virtual void OnInputMethodChanged(ECommonInputType CurrentInputType) override;
	// End of UCommonButtonBase interface

#pragma endregion
	
#pragma region ButtonExtend
public:

	// 设置按钮文本
	UFUNCTION(BlueprintCallable)
	void SetButtonText(const FText& InText);


protected:
	void RefreshButtonText();

	// 蓝图实现-更新按钮的文本
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonText(const FText& InText);

	// 蓝图实现-更新按钮的样式
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonStyle();


private:
	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	uint8 bOverride_ButtonText : 1;
	
	UPROPERTY(EditAnywhere, Category="Button", meta=( editcondition="bOverride_ButtonText" ))
	FText ButtonText;
#pragma endregion


};
