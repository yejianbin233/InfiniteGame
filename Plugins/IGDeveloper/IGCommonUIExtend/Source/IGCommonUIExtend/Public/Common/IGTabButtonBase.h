﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IGButtonBase.h"
#include "IGTabListWidgetBase.h"
#include "IGTabButtonBase.generated.h"

class UCommonLazyImage;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, meta = (DisableNativeTick))
class IGCOMMONUIEXTEND_API UIGTabButtonBase : public UIGButtonBase, public ITabButtonInterface
{
	GENERATED_BODY()

public:

	void SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject);
	void SetIconBrush(const FSlateBrush& Brush);

protected:

	UFUNCTION()
	virtual void SetTabLabelInfo_Implementation(const FTabDescriptor& TabLabelInfo) override;

private:

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonLazyImage> LazyImage_Icon;
};
