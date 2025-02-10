// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/CommonBoundActionButton.h"
#include "IGBoundActionButton.generated.h"

/**
 * 扩展 UI 按键提示按钮
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class IGCOMMONUIEXTEND_API UIGBoundActionButton : public UCommonBoundActionButton
{

	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	// 按照输入类型的不同，改变按钮样式（键鼠/平板/触屏/...）
	void HandleInputMethodChanged(ECommonInputType NewInputMethod);

	UPROPERTY(EditAnywhere, Category = "Styles")
	TSubclassOf<UCommonButtonStyle> KeyboardStyle;

	UPROPERTY(EditAnywhere, Category = "Styles")
	TSubclassOf<UCommonButtonStyle> GamepadStyle;

	UPROPERTY(EditAnywhere, Category = "Styles")
	TSubclassOf<UCommonButtonStyle> TouchStyle;
};
