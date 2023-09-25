// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UPlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//UMG�� ������Ʈ���� �޾ƿ��� ���� Ŭ����
	class UTextBlock* m_Name;
	class UImage* m_Image;
	class UProgressBar* m_HPBar;


public:
	void SetName(FString _Name);
	void SetHPBarRatio(float _ratio);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

};
