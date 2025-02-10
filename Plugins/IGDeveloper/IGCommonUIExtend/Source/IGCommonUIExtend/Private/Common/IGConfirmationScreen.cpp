// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/IGConfirmationScreen.h"

#include "CommonBorder.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Common/IGButtonBase.h"
#include "Components/DynamicEntryBox.h"
#include "Editor/WidgetCompilerLog.h"

void UIGConfirmationScreen::SetupDialog(UCommonGameDialogDescriptor* Descriptor,
                                        FCommonMessagingResultDelegate ResultCallback)
{
	Super::SetupDialog(Descriptor, ResultCallback);

	Text_Title->SetText(Descriptor->Header);
	RichText_Description->SetText(Descriptor->Body);

	EntryBox_Buttons->Reset<UIGButtonBase>([](UIGButtonBase& Button)
	{
		Button.OnClicked().Clear();
	});

	for (const FConfirmationDialogAction& Action : Descriptor->ButtonActions)
	{
		FDataTableRowHandle ActionRow;

		switch(Action.Result)
		{
		case ECommonMessagingResult::Confirmed:
			ActionRow = ICommonInputModule::GetSettings().GetDefaultClickAction();
			break;
		case ECommonMessagingResult::Declined:
			ActionRow = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case ECommonMessagingResult::Cancelled:
			ActionRow = CancelAction;
			break;
		default:
			ensure(false);
			continue;
		}

		UIGButtonBase* Button = EntryBox_Buttons->CreateEntry<UIGButtonBase>();
		Button->SetTriggeringInputAction(ActionRow);
		Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
		Button->SetButtonText(Action.OptionalDisplayText);
	}

	OnResultCallback = ResultCallback;
}

void UIGConfirmationScreen::KillDialog()
{
	Super::KillDialog();
}

void UIGConfirmationScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 鼠标点击边界内任意区域触发 OnMouseButtonDownEvent -> 关闭页面
	Border_TapToCloseZone->OnMouseButtonDownEvent.BindDynamic(this, &UIGConfirmationScreen::HandleTapToCloseZoneMouseButtonDown);
}

void UIGConfirmationScreen::CloseConfirmationWindow(ECommonMessagingResult Result)
{
	DeactivateWidget();
	OnResultCallback.ExecuteIfBound(Result);
}



FEventReply UIGConfirmationScreen::HandleTapToCloseZoneMouseButtonDown(FGeometry MyGeometry,
                                                                       const FPointerEvent& MouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = FReply::Unhandled();

	if (MouseEvent.IsTouchEvent() || MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		CloseConfirmationWindow(ECommonMessagingResult::Declined);
		Reply.NativeReply = FReply::Handled();
	}

	return Reply;
}

#if WITH_EDITOR

void UIGConfirmationScreen::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	if (CancelAction.IsNull())
	{
		CompileLog.Error(FText::Format(FText::FromString(TEXT("{0} has unset property: CancelAction.")), FText::FromString(GetName())));
	}
}

#endif