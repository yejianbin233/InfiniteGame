// Copyright Epic Games, Inc. All Rights Reserved.

#include "SCommonPreEarlyLoadingScreenWidget.h"

#include "ScreenStyle.h"
#include "Widgets/Layout/SBorder.h"

class FReferenceCollector;

#define LOCTEXT_NAMESPACE "SCommonPreEarlyLoadingScreenWidget"

void SCommonPreEarlyLoadingScreenWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SAssignNew(BorderWidget, SBorder)
		.BorderImage(FEarlyStartupScreenStyle::Get()->GetBrush(PreLoadingScreenBeforeData::STYLEPROPERTYNAME_IMAGE))
		// .BorderImage(FCoreStyle::Get().GetBrush("WhiteBrush"))
		// .BorderBackgroundColor(FLinearColor::Green)
		.Padding(0)
	];
}

void SCommonPreEarlyLoadingScreenWidget::AddReferencedObjects(FReferenceCollector& Collector)
{
	//WidgetAssets.AddReferencedObjects(Collector);
}

FString SCommonPreEarlyLoadingScreenWidget::GetReferencerName() const
{
	return TEXT("SCommonPreEarlyLoadingScreenWidget");
}

void SCommonPreEarlyLoadingScreenWidget::UpdateBorderColor(FLinearColor InColor) const
{
	if (BorderWidget)
	{
		BorderWidget->SetBorderBackgroundColor(InColor);
	}
}

#undef LOCTEXT_NAMESPACE
