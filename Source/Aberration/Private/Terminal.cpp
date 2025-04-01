// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Terminal.h"

#include "AberrationManager.h"
#include "UI/TerminalWidget.h"
#include "AberrationCharacter.h"
#include "AberrationGameState.h"
#include "AberrationPlayerController.h"
#include "DebugMacros.h"
#include "FAnswerData.h"
#include "Helper.h"
#include "MVVMGameSubsystem.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Types/MVVMViewModelContext.h"
#include "UI/TerminalViewModel.h"

class AAberrationManager;

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = !bDisable;

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	ScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));
	
	Tooltip = TEXT("Fill Report");
	
	SetRootComponent(TerminalMesh);
	ScreenWidgetComponent->SetupAttachment(RootComponent);
}

void ATerminal::OnExitRange()
{
	if (bIsFocused)
	{
		Interact();
	}
	
	ScreenWidgetComponent->SetVisibility(false);
}

void ATerminal::OnEnterRange()
{
	ScreenWidgetComponent->SetVisibility(true);
}

void ATerminal::OnConfirmReport(int SelectedAnswerIndex)
{
	if (bIsBinaryQuestionActive && SelectedAnswerIndex == 0)
	{
		bIsBinaryQuestionActive = false;
		GenerateQuestion();
		return;
	}
	
	if (Answers[SelectedAnswerIndex].bIsCorrect)
	{
		TerminalVM->SetQuestionResultTexture(QuestionNumber-1, CorrectTexture);
	} else
	{
		TerminalVM->SetQuestionResultTexture(QuestionNumber-1, WrongTexture);
	}

	float Score = Answers[SelectedAnswerIndex].bIsCorrect ? 1.f : 0.f;

	/*for (int i = 0; i < Answers.Num(); i++)
	{
		LOG("Answer[%i].bIsCorrect: %hs", i, Answers[i].bIsCorrect ? "true" : "false");
		
		if (Answers[i].bIsCorrect)
		{
			LOG("Found Correct Answer: %i", i);
			Score += 1.f;
			
			//if (!bHasMultipleAnswers)
			//{
				break;
			//}
		}
	}*/
	
	State->RegisterScoreEntry(Score);	

	if (AberrationManager->WasLastCoach())
	{
		Character->DisableInput(Controller);
		// TODO: Show score result

		GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, this, &ThisClass::ShowResults, 2.f, false);
		
		/*if (State)
		{
			State->SaveGame();
		}*/
		// Check QuestionnaireWidget::ConfirmReport for reference
	}

	OnReportHandled.Broadcast();
}

void ATerminal::ShowResults()
{
	if (State)
	{
		TerminalVM->SetupResultsScreen(State->GetFinalScorePercentage(), ScreenWidget->GetResultsDescription(State->GetPassed()));
	}
}

void ATerminal::BeginPlay()
{
	Super::BeginPlay();

	TerminalVM = NewObject<UTerminalViewModel>(UTerminalViewModel::StaticClass());

	for (int i = 0; i < 10; i++)
	{
		TerminalVM->SetQuestionResultTexture(i, DefaultTexture);
	}
	
	FMVVMViewModelContext Context;
	Context.ContextClass = UTerminalViewModel::StaticClass();
	Context.ContextName = TEXT("TerminalVM");

	const UMVVMGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>();
	Subsystem->GetViewModelCollection()->AddViewModelInstance(Context, TerminalVM);
	
	if (bDisable)
	{
		bIsInteractive = false;
		return;
	}
	
	ScreenWidget = Cast<UTerminalWidget>(ScreenWidgetComponent->GetWidget());
	
	ScreenWidget->OnConfirmReport = FOnConfirmReport::CreateUObject(this, &ThisClass::OnConfirmReport);

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
			AberrationManager->ManagerUpdateAberrationsDelegate.AddDynamic(this, &ATerminal::UpdateReport);
		}
	}
	
	State = GetWorld()->GetGameState<AAberrationGameState>();
	State->SetTerminalVM(TerminalVM);
}

void ATerminal::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ATerminal::Interact()
{
	//LOG("[%s] Interact", *GetActorLabel());

	bIsFocused = !bIsFocused;

	Character->ToggleMoveAndLookInput(!bIsFocused);
	Character->TogglePauseInput(!bIsFocused);
	
	//Controller->bShowMouseCursor = bIsFocused;
	
	if (bIsFocused)
	{
		Controller->SetViewTargetWithBlend(FocusActor, .75f);
	} else
	{
		Controller->SetViewTargetWithBlend(Character, .25f);
	}

	Character->ToggleInteractiveWidget(!bIsFocused);
	
	//GetFocusedCamera()->SetActive(bIsFocused);
}

void ATerminal::UpdateReport(FActiveAberrations Aberrations)
{
	int CoachIndex = AberrationManager->GetCurrentCoach();
	LOG("Current Coach: %d", CoachIndex);
	
	if (!AberrationManager)
	{
		LOG("Aberration Manager is null");
	}
	
	if (CoachIndex <= 1)
	{
		TerminalVM->SetupOSUpdateScreen(ScreenWidget->GetOSScreenData(CoachIndex));

		OnReportHandled.Broadcast();
		return;
	}

	ScreenWidget->UnlockButtons();
	
	const FActiveAberrations Previous = AberrationManager->GetPreviousActiveAberrations();
	PreviousAberrationsNames.Empty();
	
	if (!Previous.Array.IsEmpty() && AberrationManager)
	{
		for (int i = 0; i < AberrationManager->AberrationsData.Num(); i++)
		{
			if (Previous.Array.Contains(AberrationManager->AberrationsData[i]->ID))
			{
				PreviousAberrationsNames.AddUnique(AberrationManager->AberrationsData[i]->AberrationName);
			}
		}
	}
	
	if (State)
	{
		Stream = State->GetRandomStream();

		QuestionNumber++;
		TerminalVM->SetCurrentQuestionNumber(QuestionNumber);

		GenerateBinaryQuestion();
	}
}


void ATerminal::GenerateQuestion()
{
	Answers.Empty();
		
	TArray<FString> OtherAberrations = GetPreviousOtherThanActiveAberrationsNames();
	TArray<FString> CurrentAberrations = GetPreviousActiveAberrationsNames();

	TerminalVM->SetQuestionText(FText::FromString(TEXT("Which of these aberrations was present in the coach?")));
	ScreenWidget->bHasMultipleChoices = false;

	for (int i = 0; i < CurrentAberrations.Num(); i++)
	{
		Answers.Add(FAnswerData(CurrentAberrations[i], true));
	}
			
	for (int i = Answers.Num(); i <= 3; i++)
	{
		const FString RandomAberration = OtherAberrations[Stream.RandRange(0, OtherAberrations.Num() - 1)];
		OtherAberrations.Remove(RandomAberration);

		Answers.AddUnique(FAnswerData(RandomAberration, false));
	}
		
	Answers = ShuffleArray(Answers, Stream);

	SetAnswersText();
}

void ATerminal::GenerateBinaryQuestion()
{
	Answers.Empty();

	const bool WasAnyAberrationGenerated = AberrationManager->WasAnyAberrationGenerated();
	
	Answers.AddUnique(FAnswerData(TEXT("Yes"), WasAnyAberrationGenerated));
	Answers.AddUnique(FAnswerData(TEXT("No"), !WasAnyAberrationGenerated));
	Answers.AddUnique(FAnswerData(TEXT(""), false));
	
	TerminalVM->SetQuestionText(FText::FromString(TEXT("Have you found any aberrations in this train coach?")));

	SetAnswersText();

	bIsBinaryQuestionActive = true;
}

void ATerminal::SetAnswersText()
{
	for (int i = 0; i < 3; i++)
	{
		TerminalVM->SetAnswerText(i, FText::FromString(Answers[i].Text));
	}
}

TArray<FString> ATerminal::GetPreviousActiveAberrationsNames()
{
	return PreviousAberrationsNames;
}

TArray<FString> ATerminal::GetPreviousOtherThanActiveAberrationsNames() const
{
	TArray<FString> Names;
	
	for (int i = 0; i < AberrationManager->GetPreviousOtherThanActiveAberrations().Num(); i++)
	{
		//LOG("Other: %s", *AberrationManager->GetPreviousOtherThanActiveAberrations()[i]->AberrationName);
		Names.AddUnique(AberrationManager->GetPreviousOtherThanActiveAberrations()[i]->AberrationName);
	}
	
	return Names;
}
