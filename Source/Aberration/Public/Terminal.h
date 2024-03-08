// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terminal.generated.h"

class USpringArmComponent;
class UWidgetComponent;
class UCameraComponent;
class UWidget;

UCLASS()
class ABERRATION_API ATerminal : public AActor
{
	GENERATED_BODY()
	
public:	
	ATerminal();
	virtual void Tick(float DeltaTime) override;

	UCameraComponent* GetFocusedCamera();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly)
	UWidgetComponent* ScreenWidget;

	UPROPERTY(EditInstanceOnly)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditInstanceOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* TerminalMesh;

};
