// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TerminalButton.h"
#include "Blueprint/UserWidget.h"
#include "QuestionButton.generated.h"

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

	bool IsAnswerCorrect() const;
	void SetIsCorrect(bool IsCorrect);
private:
	bool bIsCorrect = false;
};
