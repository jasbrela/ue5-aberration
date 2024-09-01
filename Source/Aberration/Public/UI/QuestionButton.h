// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TerminalButton.h"
#include "QuestionButton.generated.h"

// TODO: use this to identify clicked button etc
DECLARE_DELEGATE_OneParam(FOnClickQuestionButtonDelegate, int)

/**
 * 
 */
UCLASS()
class ABERRATION_API UQuestionButton : public UTerminalButton
{
	GENERATED_BODY()
public:
	UQuestionButton(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	void SetOnClickQuestion(const FOnClickQuestionButtonDelegate& Callback);
	void SetIsCorrect(bool IsCorrect);
	bool IsAnswerCorrect() const;
	virtual void Reset() override;
private:	
	virtual void OnClickButton() override;
	
	bool bIsCorrect = false; //TODO: Is it necessary?
	FOnClickQuestionButtonDelegate OnClick;
	
	UPROPERTY(EditAnywhere)
	int ID = -1;

};
