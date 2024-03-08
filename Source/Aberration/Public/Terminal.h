// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Actor.h"
#include "Terminal.generated.h"

class AAberrationPlayerController;
class AAberrationCharacter;
class USpringArmComponent;
class UWidgetComponent;
class UCameraComponent;
class UWidget;

UCLASS()
class ABERRATION_API ATerminal : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	ATerminal();
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual void OnExitRange() override;
	virtual void OnEnterRange() override;

protected:
	virtual void BeginPlay() override;

private:
	bool bIsFocused = false;
	
	UPROPERTY(EditInstanceOnly)
	UWidgetComponent* ScreenWidget;

	UPROPERTY(EditInstanceOnly)
	AActor* FocusActor;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* TerminalMesh;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationCharacter* Character;
	
	UPROPERTY(VisibleInstanceOnly)
	APlayerController* Controller;

};
