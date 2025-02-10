﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActionWidget.h"
#include "IGActionWidget.generated.h"

/**
 * 扩展 ActionWidget
 */
UCLASS(BlueprintType, Blueprintable)
class IGCOMMONUIEXTEND_API UIGActionWidget : public UCommonActionWidget
{
	GENERATED_BODY()

public:

	//~ Begin UCommonActionWidget interface
	virtual FSlateBrush GetIcon() const override;
	//~ End of UCommonActionWidget interface

	/** The Enhanced Input Action that is associated with this Common Input action. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	const TObjectPtr<class UInputAction> AssociatedInputAction;

private:

	class UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
};
