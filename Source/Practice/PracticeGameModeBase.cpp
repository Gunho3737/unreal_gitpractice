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

	//UI�� ���� �������Ʈ �ε��ؿ�
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
			// �ٿ�ĳ���� ���� ==> UMainHUD_Base �κ��� �Ļ��� �������Ʈ�� �ƴϴ�.
			
		}
		else
		{
			//����Ʈ�� ���� �߰�
			m_MainHUD->AddToViewport();
		}
	}
}
