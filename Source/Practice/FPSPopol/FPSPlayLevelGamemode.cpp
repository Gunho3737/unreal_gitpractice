// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayLevelGamemode.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlayerUI/FPS_MainWidget.h"


AFPSPlayLevelGamemode::AFPSPlayLevelGamemode()
{
	ConstructorHelpers::FClassFinder<APawn> Finder(TEXT("/Script/Engine.Blueprint'/Game/FPSPopol/Character/BPC_FPSPlayer.BPC_FPSPlayer_C'"));
	if (Finder.Succeeded())
	{
		DefaultPawnClass = Finder.Class;
	}

	//����ô�Ʈ���� ������ ������ ������
	ConstructorHelpers::FClassFinder<UUserWidget> HudFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/FPSPopol/Character/CharUI/BPC_FPSMainWidget.BPC_FPSMainWidget_C'"));
	if (HudFinder.Succeeded())
	{
		m_MainHudClass = HudFinder.Class;
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
			// �ٿ�ĳ���� ���� ==> UMainHUD_Base �κ��� �Ļ��� �������Ʈ�� �ƴϴ�.

		}
		else
		{
			//����Ʈ�� ���� �߰�
			m_MainHUD->AddToViewport();
		}
	}
}
