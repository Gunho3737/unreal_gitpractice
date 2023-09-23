// Fill out your copyright notice in the Description page of Project Settings.

#include "StartMenuWidget.h"
#include "../Header/Globalheader.h"
#include "Blueprint/UserWidget.h"

void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//위젯에 있는 버튼의 이름을 입력해 세팅
	m_StartBtn = Cast<UButton>(GetWidgetFromName(FName("StartButton")));
	m_ExitBtn = Cast<UButton>(GetWidgetFromName(FName("ExitButton")));

	//UButton의 멤버변수에 함수들을 바인딩하여 입력이 들어올시 함수 실행토록 함
	if (!IsValid(m_StartBtn) || !IsValid(m_ExitBtn))
	{
		//참조실패해서 그대로 리턴
		UE_LOG(LogTemp, Warning, TEXT("Button BindFailure"));
		return;
	}
	else
	{
		m_StartBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::StartBtnClicked);
		m_StartBtn->OnHovered.AddDynamic(this, &UStartMenuWidget::StartBtnHovered);
		m_StartBtn->OnUnhovered.AddDynamic(this, &UStartMenuWidget::StartBtnUnHovered);

		m_ExitBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::EndBtnClicked);
		m_ExitBtn->OnHovered.AddDynamic(this, &UStartMenuWidget::EndBtnHovered);
		m_ExitBtn->OnUnhovered.AddDynamic(this, &UStartMenuWidget::EndBtnUnHovered);


	}
}

void UStartMenuWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UStartMenuWidget::StartBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("StartButton Click"));

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MyLevel"));
}

void UStartMenuWidget::StartBtnHovered()
{
	UE_LOG(LogTemp, Warning, TEXT("StartButton Hover"));

	UWidgetBlueprintGeneratedClass* pWidgetClass = GetWidgetTreeOwningClass();

	for (int32 i = 0; i < pWidgetClass->Animations.Num(); ++i)
	{
		if (pWidgetClass->Animations[i].GetName() == TEXT("StartButtonHoverAnimation_INST"))
		{
			PlayAnimation(pWidgetClass->Animations[i]);
			break;
		}
	}
}

void UStartMenuWidget::StartBtnUnHovered()
{
	UE_LOG(LogTemp, Warning, TEXT("StartButton UnHover"));

	UWidgetBlueprintGeneratedClass* pWidgetClass = GetWidgetTreeOwningClass();

	//위젯트리에서 애니메이션 정보를 가져와 애니메이션 이름을 받아 적용
	//위젯애니메이션이름은 내가만든이름_INST 형태로 저장
	for (int32 i = 0; i < pWidgetClass->Animations.Num(); ++i)
	{
		if (pWidgetClass->Animations[i].GetName() == TEXT("StartButtonUnHoverAnimation_INST"))
		{
			PlayAnimation(pWidgetClass->Animations[i]);
			break;
		}
	}
}

void UStartMenuWidget::EndBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("ExitButton Click"));

	//게임끄기
	UKismetSystemLibrary::QuitGame(GetWorld()
		, GetWorld()->GetFirstPlayerController()
		, EQuitPreference::Quit, true);
}

void UStartMenuWidget::EndBtnHovered()
{
	UE_LOG(LogTemp, Warning, TEXT("ExitButton Hover"));
}

void UStartMenuWidget::EndBtnUnHovered()
{
	UE_LOG(LogTemp, Warning, TEXT("ExitButton UnHover"));
}
