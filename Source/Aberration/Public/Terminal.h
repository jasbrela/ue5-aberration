// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Actor.h"
#include "Terminal.generated.h"

struct FAnswerData;
struct FActiveAberrations;
class AAberrationGameState;
class UTerminalViewModel;
class AAberrationManager;
class UTerminalWidget;
class AAberrationPlayerController;
class AAberrationCharacter;
class USpringArmComponent;
class UWidgetComponent;
class UCameraComponent;
class UWidget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerFillReportDelegate);

UCLASS()
class ABERRATION_API ATerminal : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	ATerminal();
	virtual void Tick(float DeltaTime) override;

	void Unfocus();
	virtual void Interact() override;
	virtual void OnExitRange() override;
	virtual void OnEnterRange() override;

	UFUNCTION(BlueprintCallable)
	void OnConfirmReport(int SelectedAnswerIndex);
	
	FOnPlayerFillReportDelegate OnReportHandled;

	UFUNCTION()
	void UpdateReport(FActiveAberrations Aberrations);
	TArray<FString> GetPreviousActiveAberrationsNames();
	TArray<FString> GetPreviousOtherThanActiveAberrationsNames() const;

protected:
	virtual void BeginPlay() override;

private:
	bool bReportHandled = false;
	void ShowResults();
	void GenerateQuestion();
	void GenerateBinaryQuestion();
	void SetAnswersText();

	bool bIsBinaryQuestionActive = false;
	
	FRandomStream Stream;
	bool bIsFocused = false;
	int QuestionNumber = 0;
	TArray<FAnswerData> Answers;
	FTimerHandle LoadingTimerHandle;


	UPROPERTY()
	UTerminalViewModel* TerminalVM;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<FString> PreviousAberrationsNames;

	UPROPERTY(EditInstanceOnly)
	bool bDisable = false;
	
	UPROPERTY(EditInstanceOnly)
	UWidgetComponent* ScreenWidgetComponent;

	UPROPERTY()
	UTerminalWidget* ScreenWidget;
	
	UPROPERTY(EditInstanceOnly)
	AActor* FocusActor;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* TerminalMesh;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationCharacter* Character;
	
	UPROPERTY(VisibleInstanceOnly)
	APlayerController* Controller;

	UPROPERTY(VisibleInstanceOnly)
	AAberrationManager* AberrationManager;

	UPROPERTY()
	AAberrationGameState* State;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* DefaultTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CorrectTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* HalfTexture;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* WrongTexture;

};
