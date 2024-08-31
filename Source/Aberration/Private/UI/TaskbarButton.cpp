// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/TaskbarButton.h"

UTaskbarButton::UTaskbarButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

bool UTaskbarButton::GetIsPressed()
{
	return bIsPressed;
}

void UTaskbarButton::UpdateButtonStyle(bool bPress)
{
	Button->SetStyle(bPress ? PressedStyle : DefaultStyle);

	bIsPressed = bPress;
}
