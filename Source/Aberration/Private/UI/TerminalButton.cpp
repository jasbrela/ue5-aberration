// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/TerminalButton.h"

#include "DebugMacros.h"

#include "Helper.h"


UTerminalButton::UTerminalButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

bool UTerminalButton::IsPressed() const
{
	if (!bStayPressed)
	{
		LOG_WARNING("Checking 'IsPressed' of a button that can't stay pressed.");
		return false;
	}
	return bIsPressed;
}

void UTerminalButton::RegisterButtonCallback()
{
	if (!OnClick.IsBound())
	{
		Button->OnClicked.AddDynamic(this, &UTerminalButton::OnClickButton);
	}
}

void UTerminalButton::UpdateButtonStyle() const
{
	if (!bStayPressed) return;
	//LOG("UpdateButtonStyle: Pressed: %s", BOOL_TO_TEXT(bIsPressed));
	Button->SetStyle(bIsPressed ? PressedStyle->Style : DefaultStyle->Style);
}

void UTerminalButton::Reset()
{
	bIsPressed = false;
	UpdateButtonStyle();
}

void UTerminalButton::SetOnClick(const FOnClickButtonDelegate& Callback)
{
	RegisterButtonCallback();
	
	OnClick = Callback;
}

void UTerminalButton::SetText(const FString& NewText) const
{
	Text->SetText(FText::FromString(NewText));
}

void UTerminalButton::OnClickButton() // DO NOT MAKE IT CONST
{
	if (OnClick.IsBound())
	{
		OnClick.Execute();
	}

	if (bStayPressed)
	{
		bIsPressed = !bIsPressed;
	}

	UpdateButtonStyle();
}
