// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/TerminalButton.h"


UTerminalButton::UTerminalButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UTerminalButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnClicked.AddDynamic(this, &UTerminalButton::OnClickButton);
}

bool UTerminalButton::GetIsPressed() const
{
	return bIsPressed;
}

void UTerminalButton::UpdateButtonStyle(bool bPress)
{
	Button->SetStyle(bPress ? PressedStyle->Style : DefaultStyle->Style);

	bIsPressed = bPress;
}

void UTerminalButton::SetOnClick(FOnClickTerminalButton& Callback)
{
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
}