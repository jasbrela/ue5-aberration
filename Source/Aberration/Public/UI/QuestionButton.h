// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TerminalButton.h"
#include "QuestionButton.generated.h"

// TODO: use this to identify clicked button etc
DECLARE_DELEGATE_TwoParams(FOnClickQuestionButtonDelegate, int, bool)

/**
 * 
 */
UCLASS()
class ABERRATION_API UQuestionButton : public UTerminalButton
{
	GENERATED_BODY()
public:
	UQuestionButton(const FObjectInitializer& ObjectInitializer);
	
	void SetOnClickQuestion(const FOnClickQuestionButtonDelegate& Callback);
	void SetIsCorrect(bool bIsQuestionCorrect);
	bool IsAnswerCorrect() const;
	virtual void Reset() override;
	UPROPERTY(EditAnywhere)
	int ID = -1;
private:
	virtual void OnClickButton() override;
	
	bool bIsCorrect = false; //TODO: Is it necessary?
	FOnClickQuestionButtonDelegate OnClickQuestion;
	

};
