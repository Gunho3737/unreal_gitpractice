// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"

void UMainHUDWidget::ShowInventoryUI(bool _bShow)
{
	//�κ��丮�� ������ �ʵ��� ��
	if (_bShow)
	{
		m_Inventory->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UMainHUDWidget::IsInventoryOpen()
{
	if (ESlateVisibility::Visible == m_Inventory->GetVisibility())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UMainHUDWidget::SetPlayerHPRatio(float _Ratio)
{
	m_PlayerInfo->SetHPBarRatio(_Ratio);
}

void UMainHUDWidget::SetRoughSliderValue(float _value)
{
	m_MPCInst->SetScalarParameterValue(TEXT("roughness"), _value);
}


void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerInfo = Cast<UPlayerInfoWidget>(GetWidgetFromName(FName("PlayerInfo")));
	if (!IsValid(m_PlayerInfo))
	{
		LOG(LogTemp, Error, TEXT("PlayerInfo �� ã��"));
	}

	m_Inventory = Cast<UInventory_Base>(GetWidgetFromName(FName("Inventory")));
	if (!IsValid(m_Inventory))
	{
		LOG(LogTemp, Error, TEXT("Inventory ���� �� ã��"));
	}
	else
	{
		//m_Inventory->SetVisibility(ESlateVisibility::Visible);
		m_Inventory->SetVisibility(ESlateVisibility::Hidden);
	}

	m_Slider = Cast<USlider>(GetWidgetFromName(FName("RoughSlider")));
	if (!IsValid(m_Slider))
	{
		LOG(LogTemp, Error, TEXT("Slider ���� �� ã��"));
	}
	else
	{
		m_Slider->OnValueChanged.AddDynamic(this, &UMainHUDWidget::SetRoughSliderValue);
	}

	m_MPC = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Script/Engine.MaterialParameterCollection'/Game/MyLandScape/MTC_LandScape.MTC_LandScape'"));
	m_MPCInst = GetWorld()->GetParameterCollectionInstance(m_MPC);
}

void UMainHUDWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}
