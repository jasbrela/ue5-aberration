// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "TrainDoor.h"

#include "Terminal.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ATrainDoor::ATrainDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMeshL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMeshL"));
	DoorMeshR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMeshR"));
	
	ForceCloseTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForceCloseTrigger"));
	ClosedDoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ClosedDoorCollision"));
	CloseSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("CloseSFX"));
	OpenSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("OpenSFX"));

	bIsInteractive = false;

	SetRootComponent(CloseSFX);
	
	DoorMeshL->SetupAttachment(RootComponent);
	DoorMeshR->SetupAttachment(RootComponent);
	ForceCloseTrigger->SetupAttachment(RootComponent);
	ClosedDoorCollision->SetupAttachment(RootComponent);
	OpenSFX->SetupAttachment(RootComponent);
}

void ATrainDoor::BeginPlay()
{
	Super::BeginPlay();

	Tooltip = TooltipText;

	ForceCloseTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATerminal::StaticClass()); Actor != nullptr)
	{
		if (ATerminal* Terminal = Cast<ATerminal>(Actor))
		{
			Terminal->OnReportHandled.AddDynamic(this, &ATrainDoor::ReleaseAccess);
		}
	}
}

void ATrainDoor::DoorMovement(float DeltaTime)
{	
	const float DoorRCurrentPosition = DoorMeshR->GetRelativeLocation().Y;
	const float FinalLocation = bIsOpening ? OpenDoorYLocation : ClosedDoorYLocation;

	//LOG("Current RelativePos: %f | %f", DoorCurrentPosition, FinalLocation);

	const bool NearlyEqual = FMath::IsNearlyEqual(DoorRCurrentPosition, FinalLocation, 1.f);
	const bool OffLimits = (bIsOpening && DoorRCurrentPosition > FinalLocation) || (!bIsOpening && DoorRCurrentPosition < FinalLocation);

	if (NearlyEqual || OffLimits)
	{
		if (!bIsOpening) ForceCloseDoor();
		bIsMoving = false;
		return;
	}

	const float YOffsetToAdd = Speed * DeltaTime * (bIsOpening ? 1 : -1);
	
	const FVector LocationToAdd = FVector(0, YOffsetToAdd, 0);
	DoorMeshL->AddRelativeLocation(-LocationToAdd);
	DoorMeshR->AddRelativeLocation(LocationToAdd);
}

void ATrainDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CloseDoor();
}

void ATrainDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		DoorMovement(FMath::Clamp(DeltaTime, 0.0f, 0.033f));
	}
}

void ATrainDoor::OpenDoor()
{
	if (bIsOpening) return;

	OpenSFX->Play();
	
	bIsOpening = true;
	bIsMoving = true;
	
	ClosedDoorCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATrainDoor::CloseDoor()
{
	if (!bIsOpening) return;
	CloseSFX->Play();
	bIsOpening = false;
	bIsMoving = true;
	
	ClosedDoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATrainDoor::ForceCloseDoor()
{
	if (!bCanForceClose)
	{
		bCanForceClose = true;
		return;
	}
	
	if (!DoorMeshR || !DoorMeshL)
	{
		UE_LOG(LogTemp, Error, TEXT("DoorMeshR or DoorMeshL is nullptr in ForceCloseDoor"));
		return;
	}

	ClosedDoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	bIsMoving = false;
	bIsOpening = false;
	
	const FVector LocationR = DoorMeshR->GetRelativeLocation();
	const FVector LocationL = DoorMeshL->GetRelativeLocation();
	DoorMeshR->SetRelativeLocation(FVector(LocationR.X, ClosedDoorYLocation, LocationR.Z));
	DoorMeshL->SetRelativeLocation(FVector(LocationL.X, ClosedDoorYLocation, LocationL.Z));
}

void ATrainDoor::ForceOpenDoor()
{
	bIsMoving = false;
	bIsOpening = true;
	bIsInteractive = false;
	
	const FVector LocationR = DoorMeshR->GetRelativeLocation();
	const FVector LocationL = DoorMeshL->GetRelativeLocation();
	DoorMeshR->SetRelativeLocation(FVector(LocationR.X, OpenDoorYLocation, LocationR.Z));
	DoorMeshL->SetRelativeLocation(FVector(LocationL.X, -OpenDoorYLocation, LocationL.Z));
}

void ATrainDoor::BlockNextForceClose()
{
	bCanForceClose = false;
}

void ATrainDoor::Interact()
{
	bIsInteractive = false;
	OpenDoor();
}

void ATrainDoor::OnExitRange() { }

void ATrainDoor::OnEnterRange() { }

void ATrainDoor::ReleaseAccess()
{
	bIsInteractive = true;
}

