// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Actor.h"
#include "Terminal.generated.h"

struct FActiveAberrations;
class AAberrationManager;
class UTerminalWidget;
class AAberrationPlayerController;
class AAberrationCharacter;
class USpringArmComponent;
class UWidgetComponent;
class UCameraComponent;
class UWidget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerFillReportDelegate);

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
	
	FOnPlayerFillReportDelegate PlayerFillReportDelegate;

	UFUNCTION()
	void UpdateReport(FActiveAberrations Aberrations);
	void ConfirmReport() const;
	TArray<FString> GetPreviousActiveAberrationsNames();
	TArray<FString> GetPreviousOtherThanActiveAberrationsNames() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	TArray<FString> PreviousAberrationsNames;

	UPROPERTY(EditInstanceOnly)
	bool bDisable = false;
	
	bool bIsFocused = false;
	
	UPROPERTY(EditInstanceOnly)
	UWidgetComponent* ScreenWidgetComponent;

	UPROPERTY()
	UTerminalWidget* ScreenWidget;
	
	UPROPERTY(EditInstanceOnly)
	AActor* FocusActor;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* TerminalMesh;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationCharacter* Character;
	
	UPROPERTY(VisibleInstanceOnly)
	APlayerController* Controller;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationManager* AberrationManager;
};
