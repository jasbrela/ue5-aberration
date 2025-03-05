// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "UI/TerminalWidget.h"

#include "AberrationGameState.h"
#include "AberrationPlayerController.h"
#include "DebugMacros.h"
#include "FAnswerData.h"
#include "Helper.h"
#include "Terminal.h"
#include "Components/AudioComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "UI/QuestionnaireWidget.h"

UTerminalWidget::UTerminalWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }

void UTerminalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent = NewObject<UAudioComponent>(this);
	if (AudioComponent)
	{
        AudioComponent->RegisterComponentWithWorld(GetWorld());
		AudioComponent->SetSound(MouseClickSound);
		AudioComponent->SetAutoActivate(false);
	}

	if (ACharacter* BaseCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		if (AAberrationCharacter* Character = Cast<AAberrationCharacter>(BaseCharacter))
		{
			AController* BaseController = Character->GetController();
			Controller = Cast<AAberrationPlayerController>(BaseController);
		}
	}
}

FReply UTerminalWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		AudioComponent->Play();
		Controller->bShowMouseCursor = false;
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

/*
FReply UTerminalWidget::NativeOnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (CursorImage)
	{
		const FVector2D MousePosition = MouseEvent.GetScreenSpacePosition();
		const FVector2D LocalMousePosition = MyGeometry.AbsoluteToLocal(MousePosition);

		// Update the image position
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(CursorImage->Slot))
		{
			CanvasSlot->SetPosition(LocalMousePosition);
		}
	}

	return Super::NativeOnMouseMove(MyGeometry, MouseEvent);
}

#pragma region INJECTIONS
void UTerminalWidget::Inject(UWidgetComponent* Component)
{
	WidgetComponent = Component;
	Questionnaire->Inject(WidgetComponent);
}

void UTerminalWidget::Inject(AAberrationManager* Manager)
{
	AberrationManager = Manager;
	Questionnaire->Inject(Manager);
}

void UTerminalWidget::Inject(ATerminal* TerminalParent)
{
	Terminal = TerminalParent;
	Questionnaire->Inject(TerminalParent);
}
#pragma endregion

void UTerminalWidget::InitializeTerminal()
{
	Questionnaire->SetOnSubmitQuestion(FOnSubmitYesNoQuestionDelegate::CreateUObject(this, &UTerminalWidget::GenerateQuestion));
}

void UTerminalWidget::ShowReport() const
{	
	GenerateYesNoQuestion();
}

void UTerminalWidget::OnClickDesktopIcon() const
{
	if (QuizIcon->IsPressed()) QuizIcon->OnClickAnywhere();
	if (NotesIcon->IsPressed()) NotesIcon->OnClickAnywhere();
}

void UTerminalWidget::OnClickQuiz() const
{
	if (QuizIcon->IsPressed())
	{
		OnClickAnywhere();
		//Questionnaire->Open();
	}
	
	OnClickDesktopIcon();
}

void UTerminalWidget::OnClickAnywhere() const
{
	if (QuizIcon) QuizIcon->OnClickAnywhere();
	if (NotesIcon) NotesIcon->OnClickAnywhere();
}

void UTerminalWidget::OnClickNotes() const
{
	if (NotesIcon->IsPressed())
	{
		//Notes->Open();
		OnClickAnywhere();
	}
	
	OnClickDesktopIcon();
}

void UTerminalWidget::SetAnswersText()
{
	for (int i = 0; i < 3; i++)
	{
		Questionnaire->SetAnswerText(i, Answers[i].Text);
	}
	
	WidgetComponent->RequestRedraw();
}

void UTerminalWidget::GenerateYesNoQuestion() const
{
	Questionnaire->IncreaseQuestionNumber();
	Questionnaire->SetMultipleAnswers(false);
	Questionnaire->SetQuestionTitle(TEXT("Have you found any aberrations in this train coach?"));

	const TArray<FString> CurrentAberrations = Terminal->GetPreviousActiveAberrationsNames();
	
	//LOG("Is there any aberration? %s", bIsThereAnyAberration ? TEXT("true") : TEXT("false"));

	Questionnaire->SetAnswerText(1, "Yes");
	Questionnaire->SetAnswerText(2, "No");
	Questionnaire->SetAnswerText(3, "");
	
	WidgetComponent->RequestRedraw();
}

void UTerminalWidget::GenerateQuestion()
{
	if (State)
	{
		Stream = State->GetRandomStream();
		const int QuestionType = Stream.RandRange(0, 2);

		Answers.Empty();
		//LOG("Generated question of type %i", QuestionType);
		
		TArray<FString> OtherAberrations = Terminal->GetPreviousOtherThanActiveAberrationsNames();
		TArray<FString> CurrentAberrations = Terminal->GetPreviousActiveAberrationsNames();
		
		Questionnaire->SetMultipleAnswers(QuestionType < 1);
		
		if (QuestionType >= 1) // Which were found
		{
			Questionnaire->SetQuestionTitle(TEXT("Which of these aberrations was present in the coach?"));

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
		}
		else // Which were not found
		{
			Questionnaire->SetQuestionTitle(TEXT("Which aberrations were NOT present in the coach?"));

			int AberrationsFromThisCoachQuantity = 0;
			
			if (!CurrentAberrations.IsEmpty())
			{
				AberrationsFromThisCoachQuantity = Stream.RandRange(1, FMath::Min(CurrentAberrations.Num()-1, 2));
				CurrentAberrations = ShuffleArray(CurrentAberrations, Stream);
			}

			for (int i = 0; i < 3; i++)
			{
				if (i < AberrationsFromThisCoachQuantity)
				{
					//LOG("[A] Added: %s", *CurrentAberrations[i]);
					Answers.Add(FAnswerData(CurrentAberrations[i], false));
					
					if (OtherAberrations.Contains(CurrentAberrations[i]))
					{
						OtherAberrations.Remove(CurrentAberrations[i]);
					}
				} else
				{
					const int Index = Stream.RandRange(0, OtherAberrations.Num() - 1);
					const FString RandomAberration = OtherAberrations[Index];
					OtherAberrations.RemoveAt(Index);
					//LOG("[B] Added: %s", *RandomAberration);
					Answers.Add(FAnswerData(RandomAberration, true));
				}
			}
		}

		Questionnaire->SetCanFinishQuestion(true);
		
		Answers = ShuffleArray(Answers, Stream);
		SetAnswersText();
	}
}
*/
