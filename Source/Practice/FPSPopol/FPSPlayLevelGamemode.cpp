// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayLevelGamemode.h"


AFPSPlayLevelGamemode::AFPSPlayLevelGamemode()
{
	ConstructorHelpers::FClassFinder<APawn> Finder(TEXT("/Script/Engine.Blueprint'/Game/FPSPopol/Character/BPC_FPSPlayer.BPC_FPSPlayer_C'"));
	if (Finder.Succeeded())
	{
		DefaultPawnClass = Finder.Class;
	}

	//블루플니트에서 세팅한 설정값 가져옴
	ConstructorHelpers::FClassFinder<UUserWidget> HudFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FPSPopol/Character/CharUI/BPC_FPSMainWidget.BPC_FPSMainWidget_C'"));
	if (HudFinder.Succeeded())
	{
		m_MainHudClass = HudFinder.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> GameOverHudFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FPSPopol/Character/CharUI/BPC_GameOverWidget.BPC_GameOverWidget_C'"));
	if (GameOverHudFinder.Succeeded())
	{
		m_GameOverClass = GameOverHudFinder.Class;
	}
}

AFPSPlayLevelGamemode::~AFPSPlayLevelGamemode()
{
}

void AFPSPlayLevelGamemode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainHudClass))
	{
		m_MainHUD = Cast<UFPS_MainWidget>(CreateWidget(GetWorld(), m_MainHudClass));
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

	if (IsValid(m_GameOverClass))
	{
		m_GameoverWidget = Cast<UGameoverWidget>(CreateWidget(GetWorld(), m_GameOverClass));
		if (!IsValid(m_GameoverWidget))
		{
			// 다운캐스팅 실패 ==> UMainHUD_Base 로부터 파생된 블루프린트가 아니다.

		}
		else
		{
			//뷰포트에 위젯 추가
			//화면 전체 가리도록 세팅할것
			m_GameoverWidget->AddToViewport();
			m_GameoverWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
