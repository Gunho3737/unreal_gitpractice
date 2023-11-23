// Fill out your copyright notice in the Description page of Project Settings.

#include "StartLevelGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UI/StartMenuWidget.h"

AStartLevelGameMode::AStartLevelGameMode()
{
	//UI용 위젯 블루프린트 로드해옴
	ConstructorHelpers::FClassFinder<UUserWidget> ManHUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyCharacter/StartLevel/StartLevelUI/BPC_StartLevelWidget.BPC_StartLevelWidget_C'"));

	if (ManHUD.Succeeded())
	{
		m_MainHudClass = ManHUD.Class;
	}
}

AStartLevelGameMode::~AStartLevelGameMode()
{
}

void AStartLevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainHudClass))
	{
		m_MainHUD = Cast<UStartMenuWidget>(CreateWidget(GetWorld(), m_MainHudClass));
		if (!IsValid(m_MainHUD))
		{
			// 다운캐스팅 실패 ==> UMainHUD_Base 로부터 파생된 블루프린트가 아니다.

		}
		else
		{
			//뷰포트에 위젯 추가
			m_MainHUD->AddToViewport();
		}
	}

	APlayerController* pController = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly uionly{};
	pController->SetInputMode(uionly);
	pController->bShowMouseCursor = true;
}
