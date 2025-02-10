// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/IGActionWidget.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "EnhancedInputSubsystems.h"

FSlateBrush UIGActionWidget::GetIcon() const
{
	/*
	 * 如果存在与此小组件关联的增强输入作，则搜索绑定到该作的任何键并显示这些键，而不是默认数据表设置。这包括玩家将键反弹到其他内容的情况
	 */
	if (AssociatedInputAction)
	{
		if (const UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = GetEnhancedInputSubsystem())
		{
			TArray<FKey> BoundKeys = EnhancedInputSubsystem->QueryKeysMappedToAction(AssociatedInputAction);
			FSlateBrush SlateBrush;

			const UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();
			// 尝试根据 Key 获取 CommonUI 内配置的笔刷（CommonInputBaseControllerData 类下配置）
			if (!BoundKeys.IsEmpty() && CommonInputSubsystem && UCommonInputPlatformSettings::Get()->TryGetInputBrush(SlateBrush, BoundKeys[0], CommonInputSubsystem->GetCurrentInputType(), CommonInputSubsystem->GetCurrentGamepadName()))
			{
				return SlateBrush;
			}
		}
	}
	
	return Super::GetIcon();
}

UEnhancedInputLocalPlayerSubsystem* UIGActionWidget::GetEnhancedInputSubsystem() const
{
	// 根据关联的 widget 获取 ULocalPlayer 再获取 UEnhancedInputLocalPlayerSubsystem 系统
	const UWidget* BoundWidget = DisplayedBindingHandle.GetBoundWidget();
	if (const ULocalPlayer* BindingOwner = BoundWidget ? BoundWidget->GetOwningLocalPlayer() : GetOwningLocalPlayer())
	{
		return BindingOwner->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	}
	return nullptr;
}
