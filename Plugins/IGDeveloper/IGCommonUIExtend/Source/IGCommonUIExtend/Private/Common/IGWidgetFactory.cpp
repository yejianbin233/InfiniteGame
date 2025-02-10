// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/IGWidgetFactory.h"

TSubclassOf<UUserWidget> UIGWidgetFactory::FindWidgetClassForData_Implementation(const UObject* Data) const
{
	return TSubclassOf<UUserWidget>();
}
