// Copyright Epic Games, Inc. All Rights Reserved.


#include "PracticeGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainHUDWidget.h"

APracticeGameModeBase::APracticeGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> Finder(TEXT("/Script/Engine.Blueprint'/Game/MyCharacter/Character/BPC_Grey.BPC_Grey_C'"));
	if (Finder.Succeeded())
	{
		DefaultPawnClass = Finder.Class;
	}

	//UI용 위젯 블루프린트 로드해옴
	ConstructorHelpers::FClassFinder<UUserWidget> ManHUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyCharacter/Character/UI/BPC_UserWidget.BPC_UserWidget_C'"));

	if (ManHUD.Succeeded())
	{
		m_MainHudClass = ManHUD.Class;
	}
}

APracticeGameModeBase::~APracticeGameModeBase()
{
	//if (nullptr != m_EffectMgr)
	//{
	//	m_EffectMgr->ConditionalBeginDestroy();
	//}
}

void APracticeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainHudClass))
	{
		m_MainHUD = Cast<UMainHUDWidget>(CreateWidget(GetWorld(), m_MainHudClass));
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
}
