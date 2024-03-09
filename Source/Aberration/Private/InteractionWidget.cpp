// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "Aberration/DebugMacros.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


UInteractionWidget::UInteractionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UInteractionWidget::ToggleTooltip(bool bInteractiveActorFound, FString Instruction)
{
	LOG("Toggle Tooltip: %s", bInteractiveActorFound ? TEXT("true") : TEXT("false"));
	
	if (bInteractiveActorFound)
	{
		Crosshair->SetOpacity(1);
		const FString TooltipText = FString::Printf(TEXT("[E] %s"), *Instruction);	
		Tooltip->SetText(FText::FromString(TooltipText));
		Tooltip->SetVisibility(ESlateVisibility::Visible);
	} else
	{
		Crosshair->SetOpacity(0.4);
		Tooltip->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}