// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_PlayerInfoWidget.h"
#include "Components/ProgressBar.h"

void UFPS_PlayerInfoWidget::SetHPBarRatio(float _ratio)
{
	m_HPBar->SetPercent(_ratio);
}

void UFPS_PlayerInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(FName("HPBar")));
}

void UFPS_PlayerInfoWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}
