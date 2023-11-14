// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_InfoWidget.h"

#include "../Header/GlobalHeader.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UMonster_InfoWidget::SetHPRatio(float _Ratio)
{
	m_Ratio = _Ratio;

	if (IsValid(m_HPBar))
	{
		m_HPBar->SetPercent(m_Ratio);
	}
}

void UMonster_InfoWidget::SetTextBlock(const FString& _name)
{
	m_NameSet = FText::FromString(_name);

	if (IsValid(m_Name))
	{
		m_Name->SetText(m_NameSet);
	}
}

void UMonster_InfoWidget::SetMonUIVisibilty(ESlateVisibility _opacity)
{
	if (!IsValid(m_Name) || !IsValid(m_HPBar))
	{
		return;
	}

	m_Name->SetVisibility(_opacity);
	m_HPBar->SetVisibility(_opacity);
}

void UMonster_InfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	if (!IsValid(m_Name) || !IsValid(m_HPBar))
	{
		//UE_LOG(LogTemp, Error, TEXT("Widget 찾기 실패"));
	}
	else
	{	
		//외부에서 들어온 세팅값을 멤버변수로 저장한 다음
		//제대로 생성되면 멤버변수를 가져와 내부에서 세팅
		m_Name->SetText(m_NameSet);
		//이름 안보이게 끔
		m_Name->SetVisibility(ESlateVisibility::Hidden);
		m_HPBar->SetPercent(m_Ratio);
	}

	//함수테스트용
	//SetTextBlock("MonTest");
	//SetHPRatio(0.5f);
}

void UMonster_InfoWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}
