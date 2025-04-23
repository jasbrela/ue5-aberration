// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/InteractionWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


UInteractionWidget::UInteractionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UInteractionWidget::ToggleTooltip(const bool bInteractiveActorFound, const FText& Instruction)
{
	//LOG("Toggle Tooltip: %s", bInteractiveActorFound ? TEXT("true") : TEXT("false"));
	
	if (bInteractiveActorFound)
	{
		Crosshair->SetOpacity(1);
		Tooltip->SetText(FText::Format(FText::FromString(TEXT("[E] {0}")), Instruction));
		Tooltip->SetVisibility(ESlateVisibility::Visible);
	} else
	{
		Crosshair->SetOpacity(0.4);
		Tooltip->SetVisibility(ESlateVisibility::Collapsed);
	}
}