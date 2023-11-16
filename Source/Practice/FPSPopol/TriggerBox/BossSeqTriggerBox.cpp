// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSeqTriggerBox.h"
#include "../FPSPlayLevelGamemode.h"
#include "../Player/FPSPlayer.h"


ABossSeqTriggerBox::ABossSeqTriggerBox()
{
}

void ABossSeqTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ABossSeqTriggerBox::BeginTrigger);
	OnActorEndOverlap.AddDynamic(this, &ABossSeqTriggerBox::EndTrigger);
}

void ABossSeqTriggerBox::BeginTrigger(AActor* _TriggerActor, AActor* _OtherActor)
{
	LOG(LogTemp, Warning, TEXT("LevelSequence Trigger BeginOverlap"));


	if (IsValid(m_LvSeq))
	{
		if (!IsValid(m_SequencePlayer))
		{
			FMovieSceneSequencePlaybackSettings Settings = {};
			Settings.bHideHud = true;

			m_SequencePlayer
				= ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld()
					, m_LvSeq, Settings, m_SequenceActor);

			// 레벨시퀀스 종료시 호출할 Delegate 등록
			m_SequencePlayer->OnFinished.AddDynamic(this, &ABossSeqTriggerBox::BossSeqEnd);
		}

		m_SequencePlayer->Play();

		Player = Cast<AFPSPlayer>(_OtherActor);
		if (IsValid(Player))
		{
			Player->SetSeqPlay(true);
		}

		AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(GameMode))
		{
			GameMode->GetMainHUD()->SetVisibility(ESlateVisibility::Hidden);
		}

	}
}

void ABossSeqTriggerBox::EndTrigger(AActor* _TriggerActor, AActor* _OtherActor)
{
	LOG(LogTemp, Warning, TEXT("LevelSequence Trigger EndOverlap"));

	AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(GameMode))
	{
		GameMode->GetMainHUD()->SetVisibility(ESlateVisibility::Visible);
	}
}

void ABossSeqTriggerBox::BossSeqEnd()
{
	AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(GameMode))
	{
		GameMode->GetMainHUD()->SetVisibility(ESlateVisibility::Visible);
	}

	if (IsValid(Player))
	{
		Player->SetSeqPlay(false);
	}


	Destroy();
}
