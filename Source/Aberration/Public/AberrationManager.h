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
	FActiveAberrations GetLastActiveAberrations();
	int GetCurrentCoach() const;

	void ChangeCoach(int Change);

	FOnManagerUpdateAberrationsDelegate ManagerUpdateAberrationsDelegate;
	
	TArray<FAberrationData*> AberrationsData;
	
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
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* AberrationsDataTable;
	
	void ConvertTable();
	void UpdateUnlockedAberrations();
	void GenerateNextCoachAberrations();
};
