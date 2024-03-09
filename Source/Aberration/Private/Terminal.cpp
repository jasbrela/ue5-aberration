// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"

#include "AberrationManager.h"
#include "TerminalWidget.h"
#include "Aberration/AberrationCharacter.h"
#include "Aberration/AberrationPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

class AAberrationManager;

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = false;

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	ScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));

	Tooltip = TEXT("Fill Report");
	
	SetRootComponent(TerminalMesh);
	ScreenWidgetComponent->SetupAttachment(RootComponent);
}

void ATerminal::OnExitRange()
{
	ScreenWidgetComponent->SetVisibility(false);
}

void ATerminal::OnEnterRange()
{
	ScreenWidgetComponent->SetVisibility(true);
}

void ATerminal::BeginPlay()
{
	Super::BeginPlay();
	
	ScreenWidget = Cast<UTerminalWidget>(ScreenWidgetComponent->GetWidget());
	ScreenWidget->Inject(this);

	if (ACharacter* BaseCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		Character = Cast<AAberrationCharacter>(BaseCharacter);
		
		if (Character)
		{
			AController* BaseController = Character->GetController();
			Controller = Cast<AAberrationPlayerController>(BaseController);
		}
	}

	if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AAberrationManager::StaticClass()); Actor != nullptr)
	{
		if (AAberrationManager* Manager = Cast<AAberrationManager>(Actor))
		{
			//LOG("BeginPlay %s", *GetActorLabel());
			Manager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ATerminal::UpdateReport);
		}
	}
}

void ATerminal::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ATerminal::Interact()
{
	//LOG("[%s] Interact", *GetActorLabel());

	bIsFocused = !bIsFocused;

	Controller->SetIgnoreMoveInput(bIsFocused);
	Controller->SetIgnoreLookInput(bIsFocused);
	Controller->bShowMouseCursor = bIsFocused;
	
	if (bIsFocused)
	{
		Controller->SetViewTargetWithBlend(FocusActor, 1);
	} else
	{
		Controller->SetViewTargetWithBlend(Character, 1);
	}

	Character->ToggleInteractiveWidget(!bIsFocused);
	
	//GetFocusedCamera()->SetActive(bIsFocused);
}

void ATerminal::UpdateReport(FActiveAberrations Aberrations)
{
	
	if (ScreenWidget)
	{
		ScreenWidget->ShowReport();
	}
}

void ATerminal::ConfirmReport()
{
	PlayerFillReportDelegate.Broadcast();
}
