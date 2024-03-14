// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainDoor.h"

#include "Terminal.h"
#include "DebugMacros.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ATrainDoor::ATrainDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	ForceCloseTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ForceCloseTrigger"));
	ClosedDoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ClosedDoorCollision"));
	CloseSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("CloseSFX"));
	OpenSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("OpenSFX"));

	Tooltip = TEXT("Open");
	
	SetRootComponent(DoorMesh);
	ForceCloseTrigger->SetupAttachment(RootComponent);
	ClosedDoorCollision->SetupAttachment(RootComponent);
	CloseSFX->SetupAttachment(RootComponent);
	OpenSFX->SetupAttachment(RootComponent);
}

void ATrainDoor::BeginPlay()
{
	Super::BeginPlay();

	ForceCloseTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATerminal::StaticClass()); Actor != nullptr)
	{
		if (ATerminal* Terminal = Cast<ATerminal>(Actor))
		{
			Terminal->PlayerFillReportDelegate.AddDynamic(this, &ATrainDoor::ReleaseAccess);
		}
	}
}

void ATrainDoor::DoorMovement(float DeltaTime)
{	
	const float DoorCurrentPosition = DoorMesh->GetRelativeLocation().Y;
	const float FinalLocation = bIsOpening ? OpenDoorYLocation : ClosedDoorYLocation;

	//LOG("Current RelativePos: %f | %f", DoorCurrentPosition, FinalLocation);

	const bool NearlyEqual = FMath::IsNearlyEqual(DoorCurrentPosition, FinalLocation, 1.f);
	const bool OffLimits = (bIsOpening && DoorCurrentPosition > FinalLocation) || (!bIsOpening && DoorCurrentPosition < FinalLocation);

	if (NearlyEqual || OffLimits)
	{
		if (!bIsOpening) ForceCloseDoor();
		bIsMoving = false;
		return;
	}

	const float YOffsetToAdd = Speed * DeltaTime * (bIsOpening ? 1 : -1);
	
	const FVector LocationToAdd = FVector(0, YOffsetToAdd, 0);
	DoorMesh->AddRelativeLocation(LocationToAdd);
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
		DoorMovement(DeltaTime);
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
	bIsMoving = false;
	bIsOpening = false;
	
	const FVector Location = DoorMesh->GetRelativeLocation();
	DoorMesh->SetRelativeLocation(FVector(Location.X, ClosedDoorYLocation, Location.Z));
}

void ATrainDoor::ForceOpenDoor()
{
	bIsMoving = false;
	bIsOpening = true;
	bIsInteractive = false;
	
	const FVector Location = DoorMesh->GetRelativeLocation();
	DoorMesh->SetRelativeLocation(FVector(Location.X, OpenDoorYLocation, Location.Z));
}

void ATrainDoor::Interact()
{
	OpenDoor();
	bIsInteractive = false;
}

void ATrainDoor::OnExitRange() { }

void ATrainDoor::OnEnterRange() { }

void ATrainDoor::ReleaseAccess()
{
	bIsInteractive = true;
}

