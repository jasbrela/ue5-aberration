// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TerminalViewModel.generated.h"

/**
 * 
 */
UCLASS()
class ABERRATION_API UTerminalViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	int32 GetCurrentQuestionNumber() const;
	FText GetQuestionText() const;
	FText GetAnswerText1() const;
	FText GetAnswerText2() const;
	FText GetAnswerText3() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetSeedText() const;
	
	void SetSeed(const int32 Value);
	
	void SetQuestionTexture(int Index, UTexture2D* Texture);
	void SetCurrentQuestionNumber(int32 Value);

	void SetQuestionText(const FText& Value);
	void SetAnswerText(int Index, const FText& Value);

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
#pragma endregion QuestionTextures
};
