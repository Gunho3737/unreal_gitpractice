// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Monster_InfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMonster_InfoWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class UTextBlock* m_Name;
	class UProgressBar* m_HPBar;

	FText	m_NameSet;
	float	m_Ratio;


public:
	void SetHPRatio(float _Ratio);
	void SetTextBlock(const FString& _name);

	void SetMonUIVisibilty(ESlateVisibility _opacity);

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
};
