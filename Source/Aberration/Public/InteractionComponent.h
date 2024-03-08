// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


class UCameraComponent;
class IInteractive;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABERRATION_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();
	void Interact() const;
	virtual void OnRegister() override;
	void InteractionLineTrace(UWorld* World = nullptr);

protected:
	virtual void BeginPlay() override;

private:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetInteractiveObject(IInteractive* Interactive);

	UPROPERTY(EditDefaultsOnly, Category=Interaction)
	int InteractionRange = 0;

	IInteractive* CurrentInteractiveActor;

	/*UPROPERTY(EditDefaultsOnly, Category="Interaction")
	TSubclassOf<UUserWidget> InteractionWidgetClass;
	
	UPROPERTY()
	UInteractionWidget* InteractionWidget;*/
	
	FVector GetTraceStart();
	FVector GetTraceEnd();

};
