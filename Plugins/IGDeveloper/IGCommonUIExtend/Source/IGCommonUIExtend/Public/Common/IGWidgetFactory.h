// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IGWidgetFactory.generated.h"

/**
 * 控件工厂
 */
UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew)
class IGCOMMONUIEXTEND_API UIGWidgetFactory : public UObject
{
	GENERATED_BODY()

public:
	UIGWidgetFactory() { }

	UFUNCTION(BlueprintNativeEvent)
	TSubclassOf<UUserWidget> FindWidgetClassForData(const UObject* Data) const;
};
