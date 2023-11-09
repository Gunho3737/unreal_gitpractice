// Fill out your copyright notice in the Description page of Project Settings.

#include "GameoverWidget.h"
#include "../../../Header/GlobalHeader.h"
#include "Blueprint/UserWidget.h"

void UGameoverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RestartButton = Cast<UButton>(GetWidgetFromName(FName("RestartButton")));
	BackgroundColorImage = Cast<UImage>(GetWidgetFromName(FName("BackgroundColor")));
	GameOverImage = Cast<UImage>(GetWidgetFromName(FName("GameoverImage")));

	if (!IsValid(RestartButton))
	{
		//참조실패해서 그대로 리턴
		LOG(LogTemp, Warning, TEXT("Button BindFailure"));
		return;
	}
	else
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameoverWidget::RestartBtnClicked);
		RestartButton->OnHovered.AddDynamic(this, &UGameoverWidget::RestartBtnHovered);
		RestartButton->OnUnhovered.AddDynamic(this, &UGameoverWidget::RestartBtnUnHovered);
	}
}

void UGameoverWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UGameoverWidget::RestartBtnClicked()
{
	LOG(LogTemp, Warning, TEXT("Restart BtnClicked"));
}

void UGameoverWidget::RestartBtnHovered()
{
	LOG(LogTemp, Warning, TEXT("Restart Hovered"));
}

void UGameoverWidget::RestartBtnUnHovered()
{
	LOG(LogTemp, Warning, TEXT("Restart UnHovered"));
}
