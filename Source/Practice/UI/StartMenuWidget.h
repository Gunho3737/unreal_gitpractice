// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	//Components/Button�� �����ϴ� �������� ��ư �Է��� �ޱ����ؼ� �����ϴ� Ŭ����
	UButton* m_StartBtn;
	UButton* m_EndBtn;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

public:
	UFUNCTION()
		void StartBtnClicked();
	UFUNCTION()
		void StartBtnHovered();
	UFUNCTION()
		void StartBtnUnHovered();





	UFUNCTION()
		void EndBtnClicked();
	UFUNCTION()
		void EndBtnHovered();
	UFUNCTION()
		void EndBtnUnHovered();
	
};
