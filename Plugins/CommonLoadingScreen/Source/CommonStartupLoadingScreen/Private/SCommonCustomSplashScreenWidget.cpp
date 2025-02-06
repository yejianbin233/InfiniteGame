// Copyright Epic Games, Inc. All Rights Reserved.

#include "SCommonCustomSplashScreenWidget.h"

#include "Widgets/Layout/SBorder.h"

class FReferenceCollector;

#define LOCTEXT_NAMESPACE "SCommonCustomSplashScreenWidget"

void SCommonCustomSplashScreenWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(BorderWidget, SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		.BorderBackgroundColor(FLinearColor::Blue)
		.Padding(0)
	];
}

void SCommonCustomSplashScreenWidget::AddReferencedObjects(FReferenceCollector& Collector)
{
	//WidgetAssets.AddReferencedObjects(Collector);
}

FString SCommonCustomSplashScreenWidget::GetReferencerName() const
{
	return TEXT("SCommonPreEarlyLoadingScreenWidget");
}

void SCommonCustomSplashScreenWidget::UpdateBorderColor(FLinearColor InColor) const
{
	if (BorderWidget)
	{
		BorderWidget->SetBorderBackgroundColor(InColor);
	}
}

#undef LOCTEXT_NAMESPACE
