// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolTip_Base.h"

#include "Components/TextBlock.h"

void UToolTip_Base::NativeConstruct()
{
	Super::NativeConstruct();

	m_Description = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));
}

void UToolTip_Base::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);


}