// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "FOSNotificationStateData.h"
#include "TerminalWidget.generated.h"

class AAberrationPlayerController;
class UDesktopIcon;
class AAberrationManager;
class UQuestionnaireWidget;
class UTerminalButton;
class UWidgetComponent;
class AAberrationGameState;
struct FAnswerData;
struct FActiveAberrations;
struct FTerminalButtonData;
class ATerminal;
class UCanvasPanel;
class UImage;
class UButton;
class UTextBlock;

DECLARE_DELEGATE_OneParam(FOnConfirmReport, int);


/**
 * 
 */
UCLASS()
class ABERRATION_API UTerminalWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
    UTerminalWidget(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FOnConfirmReport OnConfirmReport;

	FText GetOSBodyText(int CurrentCoach);
	FText GetOSTitle(int CurrentCoach);
	UTexture2D* GetOSImage(int CurrentCoach) const;
	float GetOSUpdatePercentage(int CurrentCoach) const;

	FText GetResultsDescription(bool Passed) const;
	
	/*

	void InitializeTerminal();
	void ShowReport() const;
	void OnClickAnywhere() const;
	void OnClickDesktopIcon() const;
	void OnClickQuiz() const;
	void OnClickNotes() const;
	
	*/
	UPROPERTY(BlueprintReadOnly)
	bool bHasMultipleChoices;

	UFUNCTION(BlueprintCallable)
	void ConfirmReport(int SelectedAnswerIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UnlockButtons();
private:
	UPROPERTY()
	UAudioComponent* AudioComponent;
	
	UPROPERTY(EditAnywhere)
	USoundCue* MouseClickSound;

	UPROPERTY()
	AAberrationPlayerController* Controller;

	UPROPERTY(EditDefaultsOnly)
	FOSNotificationStateData OSStateDataOne;

	UPROPERTY(EditDefaultsOnly)
	FOSNotificationStateData OSStateDataTwo;

	UPROPERTY(EditDefaultsOnly, meta = (MultiLine = true))
	FText PositiveResultsDescription;
	
	UPROPERTY(EditDefaultsOnly, meta = (MultiLine = true))
	FText NegativeResultsDescription;
};
