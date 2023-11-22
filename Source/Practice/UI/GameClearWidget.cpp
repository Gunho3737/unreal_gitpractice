// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClearWidget.h"

void UGameClearWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameClearBG = Cast<UImage>(GetWidgetFromName(FName("BackImage")));
	GameClearImage = Cast<UImage>(GetWidgetFromName(FName("Thankyou")));
}

void UGameClearWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UGameClearWidget::SetWidgetOpacity(float _opacity)
{
	GameClearBG->SetOpacity(_opacity);
	GameClearImage->SetOpacity(_opacity);
}
