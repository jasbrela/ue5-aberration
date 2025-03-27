// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vestibule.generated.h"

class ATrainDoor;
class AAberrationManager;
class UBoxComponent;

UCLASS()
class ABERRATION_API AVestibule : public AActor
{
	GENERATED_BODY()
	
public:	
	AVestibule();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle DelayBeforeClosingDoor;
	void ForceCloseDoor();
	
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(EditInstanceOnly)
	AActor* TeleportTo;

	/*UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;*/

	UPROPERTY(EditInstanceOnly)
	ATrainDoor* Door;

	UPROPERTY(EditInstanceOnly)
	bool bCanTeleport;

	// Should be only 1 or -1.
	UPROPERTY(EditInstanceOnly, meta=(ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"));
	int TeleportValue;

	UPROPERTY(EditInstanceOnly)
	AVestibule* OtherVestibule;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector GetRelativePosition(const FVector& Offset) const;

	FVector GetOffset(const AActor* Actor) const;
	
	FVector Location;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationManager* AberrationManager;
};
