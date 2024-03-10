// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"

#include "AberrationManager.h"
#include "TerminalWidget.h"
#include "AberrationCharacter.h"
#include "AberrationPlayerController.h"
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
			AberrationManager = Manager;
			//LOG("BeginPlay %s", *GetActorLabel());
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ATerminal::UpdateReport);
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
	if (AberrationManager->GetCurrentCoach() <= 1)
	{
		ConfirmReport();
		return;
	}
	
	ScreenWidget->ResetCorrectAnswers();

	const FActiveAberrations Last = AberrationManager->GetLastActiveAberrations();
	
	if (Last.Array.Num() > 0 && AberrationManager)
	{
		for (int i = 0; i < AberrationManager->AberrationsData.Num(); i++)
		{
			if (Last.Array.Contains(AberrationManager->AberrationsData[i]->ID))
			{
				ActiveAberrationsNames.AddUnique(AberrationManager->AberrationsData[i]->AberrationName);
			}
		}
		if (ScreenWidget) ScreenWidget->SetCorrectAnswer(1, true);
	} else
	{
		if (ScreenWidget) ScreenWidget->SetCorrectAnswer(2, true);
	}
	
	if (ScreenWidget)
	{
		ScreenWidget->ShowReport();
	}
}

void ATerminal::ConfirmReport()
{
	PlayerFillReportDelegate.Broadcast();
}

TArray<FString> ATerminal::GetActiveAberrationsNames()
{
	return ActiveAberrationsNames;
}
