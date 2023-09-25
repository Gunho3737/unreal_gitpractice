// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerInfoWidget::SetName(FString _Name)
{
	m_Name->SetText(FText::FromString(_Name));
}

void UPlayerInfoWidget::SetHPBarRatio(float _ratio)
{
	m_HPBar->SetPercent(_ratio);
}

void UPlayerInfoWidget::SetMPBarRatio(float _ratio)
{
	m_MPBar->SetPercent(_ratio);
}

void UPlayerInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Name = Cast<UTextBlock>(GetWidgetFromName(FName("CharacterName")));
	m_Image = Cast<UImage>(GetWidgetFromName(FName("Portrait")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(FName("HPBar")));

	SetName("GreyStone");
	SetHPBarRatio(0.5f);
}

void UPlayerInfoWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}
