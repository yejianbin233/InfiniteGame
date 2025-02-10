// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IGWidgetFactory.h"
#include "IGWidgetFactory_Class.generated.h"

/**
 * 
 */
UCLASS()
class IGCOMMONUIEXTEND_API UIGWidgetFactory_Class : public UIGWidgetFactory
{
	GENERATED_BODY()

public:
	UIGWidgetFactory_Class() { }

	virtual TSubclassOf<UUserWidget> FindWidgetClassForData_Implementation(const UObject* Data) const override;
	
protected:
	UPROPERTY(EditAnywhere, Category = ListEntries, meta = (AllowAbstract))
	TMap<TSoftClassPtr<UObject>, TSubclassOf<UUserWidget>> EntryWidgetForClass;
};
