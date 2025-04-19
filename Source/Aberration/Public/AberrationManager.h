// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "FAberrationData.h"
#include "FActiveAberrations.h"
#include "GameFramework/Actor.h"
#include "AberrationManager.generated.h"

class AVestibule;
class ACoachID;
class AAberrationGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManagerUpdateAberrationsDelegate, FActiveAberrations, ActiveAberrations);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReachedTrainMidpoint, FActiveAberrations, ActiveAberrations);

UCLASS()
class ABERRATION_API AAberrationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAberrationManager();
	virtual void Tick(float DeltaTime) override;

	FActiveAberrations GetActiveAberrations();
	bool WasAnyAberrationGenerated() const;
	FActiveAberrations GetPreviousActiveAberrations();
	TArray<FAberrationData*> GetPreviousOtherThanActiveAberrations();
	int GetCurrentCoach() const;
	void ChangeCoach(int Change);
	bool WasLastCoach() const;
	int GetNumberOfCoaches() const;
	void SetFrontVestibule(AVestibule* Vestibule);
	UFUNCTION()
	void OnConfirmReport();

	FOnManagerUpdateAberrationsDelegate ManagerUpdateAberrationsDelegate;
	FOnPlayerReachedTrainMidpoint PlayerReachedTrainMidpoint;
	
	TArray<FAberrationData*> AberrationsData;
	
protected:
	virtual void BeginPlay() override;

private:
	void GenerateSeed();
	
	UPROPERTY()
	AVestibule* FrontVestibule;
	
	UPROPERTY(EditAnywhere)
	bool bOverrideSeed = false;
	UPROPERTY(EditAnywhere)
	int Seed = 0;

	UPROPERTY(EditAnywhere)
	int AccumulatedChanceBuff = 10;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", ClampMax="100", UIMin="0", UIMax="100"))
	int GenerateAberrationsChance = 0;

	/*UPROPERTY(EditInstanceOnly)
	ACoachID* BackID;

	UPROPERTY(EditInstanceOnly)
	ACoachID* FrontID;*/

	UPROPERTY()
	AAberrationGameState* AberrationState;
		
	FRandomStream RandomStream;
	FTimerHandle BeginPlayDelayTimerHandle;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<FActiveAberrations> CoachAberrations;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<int> AvailableAberrations;
	
	TArray<FAberrationData*> OtherThanActiveAberrations;
	TArray<FAberrationData*> PreviousOtherThanActiveAberrations;
	TArray<int> UnlockedAberrations;
	TArray<int> ExcludedAberrations;
	
	UPROPERTY(EditAnywhere)
	int NumberOfCoaches = 1;
	
	UPROPERTY(VisibleInstanceOnly)
	int CurrentCoach = 0;

	UPROPERTY(VisibleInstanceOnly)
	int AccumulatedWithoutAberrations = 0;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* AberrationsDataTable;
	
	void ConvertTable();
	void UpdateUnlockedAberrations();
	void GenerateNextCoachAberrations();
};
