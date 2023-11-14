// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayLevelGamemode.h"



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

	if (m_StartSeq != nullptr)
	{
		FMovieSceneSequencePlaybackSettings Settings = {};
		Settings.bHideHud = true;
		Settings.bHidePlayer = true;

		m_SequencePlayer
			= ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld()
				, m_StartSeq, Settings, m_SequenceActor);

		m_SequencePlayer->Play();
	}


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
			//m_MainHUD->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (IsValid(m_GameOverClass))
	{
		m_GameoverWidget = Cast<UGameoverWidget>(CreateWidget(GetWorld(), m_GameOverClass));
		if (!IsValid(m_GameoverWidget))
		{
			// �ٿ�ĳ���� ���� ==> UMainHUD_Base �κ��� �Ļ��� �������Ʈ�� �ƴϴ�.

		}
		else
		{
			//����Ʈ�� ���� �߰�
			//ȭ�� ��ü �������� �����Ұ�
			m_GameoverWidget->AddToViewport();
			m_GameoverWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}





	// �÷��̾� ��Ʈ�ѷ��� �Է¸�带 Game ���� ��ȯ�Ѵ�.
	APlayerController* pController = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly gonly{};
	pController->SetInputMode(gonly);
	pController->bShowMouseCursor = false;

}

void AFPSPlayLevelGamemode::StartSequenceEnd()
{
	//������ �������� UI����
	//m_MainHUD->SetVisibility(ESlateVisibility::Visible);
}
