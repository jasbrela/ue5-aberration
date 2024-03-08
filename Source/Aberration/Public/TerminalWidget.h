// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TerminalWidget.generated.h"

class UCheckBox;
class UCanvasPanel;
class UImage;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ABERRATION_API UTerminalWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UTerminalWidget(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* QuestionsCanvas;

	UPROPERTY(EditDefaultsOnly)
	UTexture* SuccessTexture;

	UPROPERTY(EditDefaultsOnly)
	UTexture* QuestionTexture;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestionNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Question;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option1Text;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Option1;
	
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option2Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Option2;

	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Option3Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Option3;

	
	UPROPERTY(meta = (BindWidget))
	UButton* Confirm;
};
