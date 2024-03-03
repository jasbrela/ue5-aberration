// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAberrationData.h"
#include "FActiveAberrations.h"
#include "GameFramework/Actor.h"
#include "AberrationManager.generated.h"

enum class EAberrationDifficulty;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManagerUpdateAberrationsDelegate, FActiveAberrations, ActiveAberrations);

UCLASS()
class ABERRATION_API AAberrationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAberrationManager();
	virtual void Tick(float DeltaTime) override;

	FActiveAberrations GetActiveAberrations();

	void ChangeCoach(int Change);

	FOnManagerUpdateAberrationsDelegate ManagerUpdateAberrationsDelegate;
	
protected:
	virtual void BeginPlay() override;

private:
	FRandomStream RandomStream;
	FTimerHandle BeginPlayDelayTimerHandle;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<FActiveAberrations> CoachAberrations;

	TArray<int> AvailableAberrations;

	UPROPERTY(VisibleInstanceOnly)
	TArray<int> UnlockedAberrations;
	
	UPROPERTY(EditAnywhere)
	int NumberOfCoaches;
	
	UPROPERTY(VisibleInstanceOnly)
	int CurrentCoach = 0;

	UPROPERTY(EditAnywhere)
	int Seed;
	
	// If checked, game will always run using the "Seed" value.
	UPROPERTY(EditAnywhere)
	bool OverrideSeed = false;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* AberrationsDataTable;

	TArray<FAberrationData*> AberrationsData;

	void ConvertTable();
	void GenerateSeed();
	void UpdateUnlockedAberrations();
	void GenerateNextCoachAberrations();
};
