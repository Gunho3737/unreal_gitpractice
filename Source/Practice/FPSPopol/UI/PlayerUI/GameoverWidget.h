// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "GameoverWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UGameoverWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//Components/Button에 존재하는 위젯에서 버튼 입력을 받기위해서 제공하는 클래스
	UButton* RestartButton;
	UImage* BackgroundColorImage;
	UImage* GameOverImage;

	bool fadeon;
	float opacity;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

	void StartFadeIn();
	void SetWidgetOpacity(float _opacity);

public:
	UFUNCTION()
		void RestartBtnClicked();
	UFUNCTION()
		void RestartBtnHovered();
	UFUNCTION()
		void RestartBtnUnHovered();
};
