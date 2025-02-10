// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/IGBoundActionButton.h"

#include "CommonInputSubsystem.h"

void UIGBoundActionButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UCommonInputSubsystem* InputSubsystem = GetInputSubsystem())
	{
		// 监听输入系统的变化
		InputSubsystem->OnInputMethodChangedNative.AddUObject(this, &ThisClass::HandleInputMethodChanged);
		HandleInputMethodChanged(InputSubsystem->GetCurrentInputType());
	}
}

void UIGBoundActionButton::HandleInputMethodChanged(ECommonInputType NewInputMethod)
{
	TSubclassOf<UCommonButtonStyle> NewStyle = nullptr;

	if (NewInputMethod == ECommonInputType::Gamepad)
	{
		NewStyle = GamepadStyle;
	}
	else if (NewInputMethod == ECommonInputType::Touch)
	{
		NewStyle = TouchStyle;
	}
	else
	{
		NewStyle = KeyboardStyle;
	}

	if (NewStyle)
	{
		SetStyle(NewStyle);
	}
}
