// Copyright (c) 2024, Jasbrela. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TerminalButton.h"
#include "DesktopIcon.generated.h"

class UImage;
class UBorder;
/**
 * 
 */
UCLASS()
class ABERRATION_API UDesktopIcon : public UTerminalButton
{
	GENERATED_BODY()
public:
	UDesktopIcon(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;
	virtual void UpdateButtonStyle() const override;
	void OnClickAnywhere();
	
protected:
	
private:
	virtual void OnClickButton() override;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(EditAnywhere)
	FSlateBrush IconBrush;
	
	UPROPERTY(EditAnywhere)
	FText IconText;
	
	UPROPERTY(meta = (BindWidget))
	UBorder* Background;
};
