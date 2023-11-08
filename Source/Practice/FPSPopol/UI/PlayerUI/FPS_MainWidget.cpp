// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_MainWidget.h"
#include "../../../Header/GlobalHeader.h"
#include "Components/Image.h"

void UFPS_MainWidget::SetPlayerHPRatio(float _Ratio)
{
	m_PlayerInfo->SetHPBarRatio(_Ratio);
}

void UFPS_MainWidget::UIOff()
{
	m_Crosshair->SetVisibility(ESlateVisibility::Hidden);
}

void UFPS_MainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Crosshair = Cast<UImage>(GetWidgetFromName(FName("CrossHair")));

	m_PlayerInfo = Cast<UFPS_PlayerInfoWidget>(GetWidgetFromName(FName("FPSPlayerInfo")));
	if (!IsValid(m_PlayerInfo))
	{
		LOG(LogTemp, Error, TEXT("PlayerInfo ¸ø Ã£À½"));
	}
}

void UFPS_MainWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}
