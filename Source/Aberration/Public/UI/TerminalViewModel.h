// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
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

	int32 GetCurrentQuestionNumber() const;
	FText GetQuestionText() const;
	FText GetAnswerText1() const;
	FText GetAnswerText2() const;
	FText GetAnswerText3() const;

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

	void SetOSUpdateTitle(const FText& Value);
	void SetOSUpdateBodyText(const FText& Value);
	void SetOSUpdateImage(UTexture2D* Value);
	void SetOSUpdatePercentage(float Value);

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	int32 CurrentQuestionNumber;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter, Getter)
	FText QuestionText;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Getter)
	FText AnswerText1;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Getter)
	FText AnswerText2;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Getter)
	FText AnswerText3;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	int32 Seed;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	FText OSUpdateTitle;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	FText OSUpdateBodyText;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	UTexture2D* OSUpdateImage;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess), Setter)
	float OSUpdatePercentage;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	bool ShowOSUpdateScreen = true;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	bool ShowResultsScreen = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText AccuracyScore = FText::FromString(TEXT("0%"));

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta = (AllowPrivateAccess))
	FText ResultsDescription = FText::FromString(TEXT("A REALLY LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG LONG TEXT"));;
	
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
