// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/DesktopIcon.h"

#include "DebugMacros.h"
#include "Components/Border.h"
#include "Components/Image.h"

UDesktopIcon::UDesktopIcon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UDesktopIcon::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (Icon)
	{
		Text->SetText(IconText);
		IconBrush.ImageSize = FVector2D(128, 128);
		Icon->SetBrush(IconBrush);
	}
}

void UDesktopIcon::NativeConstruct() { Super::NativeConstruct(); }

void UDesktopIcon::OnClickAnywhere(const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPressed = false;
		UpdateButtonStyle();
	}
}

void UDesktopIcon::UpdateButtonStyle() const
{
	FLinearColor Color = Background->GetBrushColor();
	Color.A = bIsPressed ? 0xFF : 0x00;
	Background->SetBrushColor(Color);
}

void UDesktopIcon::OnClickButton()
{
	if (bIsPressed)
	{
		if (OnClick.IsBound())
		{
			OnClick.Execute();
		}
	}
	
	bIsPressed = !bIsPressed;

	UpdateButtonStyle();
}

