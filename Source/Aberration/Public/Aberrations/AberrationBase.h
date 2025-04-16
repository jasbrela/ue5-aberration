// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AberrationManager.h"
#include "GameFramework/Actor.h"
#include "AberrationBase.generated.h"

UCLASS(Abstract)
class ABERRATION_API AAberrationBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAberrationBase();

	UFUNCTION()
	virtual void Activate();
	
	UFUNCTION()
	virtual void Deactivate();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// The ID of the aberration must match their ID in Aberrations' DataTable
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	int ID = 0;
	
private:
	UPROPERTY(VisibleInstanceOnly)
	AAberrationManager* AberrationManager;
	
	UFUNCTION()
	virtual void AberrationTick(float DeltaTime);
	
	UPROPERTY(EditDefaultsOnly, Category="Aberration")
	bool bWaitUntilMidpointIsReached = false;
	
	UFUNCTION()
	void NotifyMidpointReached(FActiveAberrations Aberrations);
	UFUNCTION()
	void NotifyAberrationChanged(FActiveAberrations Aberrations);

	bool bIsActive = false;
};

