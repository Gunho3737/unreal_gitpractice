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

	fadeon = false;

	SetWidgetOpacity(0.0f);

}

void UGameoverWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);

	if (fadeon == true)
	{
		//2초가 되면 오파시티 1 되서 보임
		opacity += (_DT * 0.5f);
		if (opacity <= 1.0f)
		{
			SetWidgetOpacity(opacity);
		}
	}

}

void UGameoverWidget::StartFadeIn()
{
	if (fadeon == true)
	{
		return;
	}

	fadeon = true;
	opacity = 0.0f;
}

void UGameoverWidget::SetWidgetOpacity(float _opacity)
{
	RestartButton->SetRenderOpacity(_opacity);
	BackgroundColorImage->SetRenderOpacity(_opacity);
	GameOverImage->SetRenderOpacity(_opacity);
}


void UGameoverWidget::RestartBtnClicked()
{
	LOG(LogTemp, Warning, TEXT("Restart BtnClicked"));
}

void UGameoverWidget::RestartBtnHovered()
{
	LOG(LogTemp, Warning, TEXT("Restart Hovered"));

	UWidgetBlueprintGeneratedClass* pWidgetClass = GetWidgetTreeOwningClass();

	for (int32 i = 0; i < pWidgetClass->Animations.Num(); ++i)
	{
		if (pWidgetClass->Animations[i].GetName() == TEXT("RestartBtnAnimation_INST"))
		{
			//무한루프하도록 세팅
			PlayAnimation(pWidgetClass->Animations[i], 0.0f, 0);
			break;
		}
	}
}

void UGameoverWidget::RestartBtnUnHovered()
{
	LOG(LogTemp, Warning, TEXT("Restart UnHovered"));
	UWidgetBlueprintGeneratedClass* pWidgetClass = GetWidgetTreeOwningClass();

	for (int32 i = 0; i < pWidgetClass->Animations.Num(); ++i)
	{
		if (pWidgetClass->Animations[i].GetName() == TEXT("RestartBtnAnimation_INST"))
		{
			StopAnimation(pWidgetClass->Animations[i]);
			break;
		}
	}
}
