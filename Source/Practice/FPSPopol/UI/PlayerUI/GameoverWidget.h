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
	//Components/Button�� �����ϴ� �������� ��ư �Է��� �ޱ����ؼ� �����ϴ� Ŭ����
	UButton* RestartButton;
	UImage* BackgroundColorImage;
	UImage* GameOverImage;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

public:
	UFUNCTION()
		void RestartBtnClicked();
	UFUNCTION()
		void RestartBtnHovered();
	UFUNCTION()
		void RestartBtnUnHovered();
};
