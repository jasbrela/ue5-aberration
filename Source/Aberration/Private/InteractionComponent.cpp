// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/InteractionComponent.h"

#include "Interactive.h"
#include "DebugMacros.h"
#include "Camera/CameraComponent.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::Interact() const
{
	if (CurrentInteractiveActor != nullptr)
	{
		CurrentInteractiveActor->Interact();
	}
}


void UInteractionComponent::InteractionLineTrace(UWorld* World)
{
	if (World == nullptr) return;
	if (GetOwner() == nullptr) return;

	LOG("[%s] Start: %s End: %s", *GetOwner()->GetActorLabel(), *GetTraceStart().ToString(), *GetTraceEnd().ToString());

	FHitResult Hit;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	
	World->LineTraceSingleByChannel(Hit, GetTraceStart(), GetTraceEnd(), ECollisionChannel::ECC_Visibility, QueryParams);
	
	DrawDebugLine(World, GetTraceStart(), GetTraceEnd(), FColor::Orange, true);

	AActor* ActorHit = Hit.GetActor();
	
	if (Hit.bBlockingHit && IsValid(ActorHit))
	{
		LOG("Three: %s", *ActorHit->GetActorLabel());
		if (IInteractive* Interactive = Cast<IInteractive>(ActorHit))
		{
			LOG("Four");
			if (CurrentInteractiveActor != Interactive) {
				
				if (Interactive->bIsInteractive)
				{
					SetInteractiveObject(Interactive);
					//InteractionWidget->ToggleInteraction(true, CurrentInteractiveActor->Tooltip);
					CurrentInteractiveActor->OnEnterRange();
				} else
				{
					SetInteractiveObject(nullptr);
					//InteractionWidget->ToggleInteraction(false);
				}
			}
			else if (!CurrentInteractiveActor->bIsInteractive)
			{
				SetInteractiveObject(nullptr);
				/*CurrentInteractiveActor->OnExitRange();
				CurrentInteractiveActor = nullptr;*/
				//InteractionWidget->ToggleInteraction(false);
			}
		}
	} else
	{
		SetInteractiveObject(nullptr);
		/*if (CurrentInteractiveActor != nullptr)
		{
			CurrentInteractiveActor->OnExitRange();
			CurrentInteractiveActor = nullptr;
			InteractionWidget->ToggleInteraction(false);
			
			//UE_LOG(LogTemp, Warning, TEXT("No Interactive"));
		}*/
	}
}

void UInteractionComponent::SetInteractiveObject(IInteractive* Interactive)
{
	if (CurrentInteractiveActor == Interactive) return;
	//LOG("SetInteractiveObject, %s, %s", (CurrentInteractiveActor == nullptr ? TEXT("nullptr") : TEXT("actor")), (CurrentInteractiveActor == nullptr ? TEXT("nullptr") : TEXT("actor")));

	if (CurrentInteractiveActor != nullptr)
	{
		CurrentInteractiveActor->OnExitRange();
	}

	CurrentInteractiveActor = Interactive;

	if (CurrentInteractiveActor != nullptr)
	{
		CurrentInteractiveActor->OnEnterRange();
	}
	
		
	//FString TooltipText = CurrentInteractiveActor != nullptr ? TEXT("[E] " + Interactive->Tooltip) : TEXT("");
	//InteractionWidget->ToggleTooltip(CurrentInteractiveActor != nullptr, TooltipText);
}

FVector UInteractionComponent::GetTraceStart()
{
	/*if (PlayerCamera)
	{
		return PlayerCamera->GetComponentLocation();
	}
	*/
	
	return FVector::Zero();
}

FVector UInteractionComponent::GetTraceEnd()
{
	/*if (PlayerCamera)
	{
		LOG("[%s] Interaction Range: %i", *GetOwner()->GetActorLabel(), InteractionRange);
		//return (GetTraceStart() + PlayerCamera->GetForwardVector() * InteractionRange);
	}
	*/
	
	return FVector::Zero();
}

void UInteractionComponent::BeginPlay() { Super::BeginPlay(); }
void UInteractionComponent::OnRegister() { Super::OnRegister(); }
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
