// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "FOSNotificationStateData.h"
#include "MVVMViewModelBase.h"
#include "TerminalViewModel.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequireUpdateOSScreen, int, QuestionNumber);

UCLASS()
class ABERRATION_API UTerminalViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	FOnRequireUpdateOSScreen OnRequireUpdateOSScreen;

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetSeedText() const;

	UFUNCTION(BlueprintCallable)
	void SetLocalMousePosition(FVector2D Position);
	
	void SetSeed(const int32 Value);
	void SetupResultsScreen(const int32 Accuracy, const FText& Description);
	
	void SetQuestionResultTexture(int Index, UTexture2D* Texture);
	void SetCurrentQuestionNumber(int32 Value);

	void SetQuestionText(const FText& Value);
	void SetAnswerText(int Index, const FText& Value);

	void SetupOSUpdateScreen(const FOSNotificationStateData& Data);
	void SetOSUpdateBodyText(const FText& Value);
	void SetOSUpdateImage(UTexture2D* Value);
	void SetOSUpdatePercentage(float Value);

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	int32 CurrentQuestionNumber;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	FText QuestionText;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText AnswerText1;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText AnswerText2;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText AnswerText3;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	bool ShowThirdAnswerButton;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	int32 Seed;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText OSUpdateTitle;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText OSUpdateBodyText;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* OSUpdateImage;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	float OSUpdatePercentage;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	bool ShowOSUpdateScreen = true;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	bool ShowResultsScreen = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText AccuracyScore = FText::FromString(TEXT("0%"));

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText ResultsDescription = FText::FromString(TEXT("A REALLY LONG TEXT"));
	
#pragma region QuestionTextures
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture0;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture1;
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture2;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture3;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture4;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture5;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture6;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture7;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture8;	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	UTexture2D* QuestionTexture9;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	FVector2D LocalMousePosition;
#pragma endregion QuestionTextures
};
