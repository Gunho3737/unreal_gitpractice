// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UGameClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UImage* GameClearBG;
	UImage* GameClearImage;
	float opacity;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

	void SetWidgetOpacity(float _opacity);
};
