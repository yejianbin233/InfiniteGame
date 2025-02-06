// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ScreenStyle.generated.h"

/**
 * 
 */
UCLASS()
class COMMONSTARTUPLOADINGSCREEN_API UScreenStyle : public UObject
{
	GENERATED_BODY()
};


namespace PreLoadingScreenBeforeData
{
	static const FName PLUGIN_NAME(TEXT("CommonLoadingScreen"));
	static const FName RUNTIME_DEPENDENCIES_RELATIVE_PATH(TEXT("Resources"));
	static const FName STYLEPROPERTYNAME_IMAGE(TEXT("Image"));
	static const FName IMAGE_FILENAME(TEXT("Smile"));
	static const FVector2D IMAGE_SIZE(512, 512);
}


class FEarlyStartupScreenStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static TSharedPtr< class ISlateStyle > Get();
	static FName GetStyleSetName();

private:
	static TSharedPtr< class FSlateStyleSet > StyleSet;
};