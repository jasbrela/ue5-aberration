// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Actor.h"
#include "TrainDoor.generated.h"

class UBoxComponent;

UCLASS()
class ABERRATION_API ATrainDoor : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	ATrainDoor();
	virtual void Tick(float DeltaTime) override;
	void OpenDoor();
	void CloseDoor();
	void ForceCloseDoor();
	void ForceOpenDoor();
	void BlockNextForceClose();
	
	virtual void Interact() override;
	virtual void OnExitRange() override;
	virtual void OnEnterRange() override;

protected:
	UFUNCTION()
	void ReleaseAccess();
	
	virtual void BeginPlay() override;
	
private:
	bool bIsMoving = false;
	bool bIsOpening = false;
	bool bCanForceClose = true;

	void DoorMovement(float DeltaTime);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category="Door")
	float OpenDoorYLocation = 113;
	
	UPROPERTY(EditAnywhere, Category="Door")
	float ClosedDoorYLocation = 270;

	UPROPERTY(EditAnywhere, Category="Door")
	float Speed = 200;

	UPROPERTY(EditInstanceOnly, Category="Door")
	UStaticMeshComponent* DoorMeshL;

	UPROPERTY(EditInstanceOnly, Category="Door")
	UStaticMeshComponent* DoorMeshR;

	UPROPERTY(EditInstanceOnly, Category="Door")
	UBoxComponent* ForceCloseTrigger;

	UPROPERTY(EditInstanceOnly, Category="Door")
	UBoxComponent* ClosedDoorCollision;

	UPROPERTY(EditInstanceOnly, Category="Door")
	UAudioComponent* OpenSFX;
	
	UPROPERTY(EditInstanceOnly, Category="Door")
	UAudioComponent* CloseSFX;
};
