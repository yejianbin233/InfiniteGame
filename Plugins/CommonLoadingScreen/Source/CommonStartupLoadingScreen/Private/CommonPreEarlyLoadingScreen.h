// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PreLoadScreenBase.h"
#include "SCommonPreEarlyLoadingScreenWidget.h"

class SWidget;

class FCommonPreEarlyLoadingScreen : public FPreLoadScreenBase
{
public:
	
    /*** IPreLoadScreen Implementation ***/
	virtual void Init() override;
    virtual EPreLoadScreenTypes GetPreLoadScreenType() const override { return EPreLoadScreenTypes::EarlyStartupScreen; }
    virtual TSharedPtr<SWidget> GetWidget() override { return EngineLoadingWidget; }

	virtual void CleanUp() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsDone() const override;

protected:
	FThreadSafeCounter IsDoneCounter;
	double DonableLastTime = 0;
	
private:

    TSharedPtr<SCommonPreEarlyLoadingScreenWidget> EngineLoadingWidget;
};
