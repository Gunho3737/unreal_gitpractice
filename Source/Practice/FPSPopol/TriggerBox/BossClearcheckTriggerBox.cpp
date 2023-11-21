// Fill out your copyright notice in the Description page of Project Settings.


#include "BossClearcheckTriggerBox.h"
#include "../FPSPlayLevelGamemode.h"
#include "../Player/FPSPlayer.h"

ABossClearcheckTriggerBox::ABossClearcheckTriggerBox()
	: MonsterCount(0)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossClearcheckTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	//현재 이 트리거 박스는 몬스터랑만 겹치는중
	OnActorBeginOverlap.AddDynamic(this, &ABossClearcheckTriggerBox::BeginTrigger);
	OnActorEndOverlap.AddDynamic(this, &ABossClearcheckTriggerBox::EndTrigger);

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
			m_SequencePlayer->OnFinished.AddDynamic(this, &ABossClearcheckTriggerBox::TeleporterSeqEnd);
		}
	}

}

void ABossClearcheckTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//LOG(Monster, Warning, TEXT("BossFight Activate"));

	if (MonsterCount == 0) 
	{
		LOG(Monster, Warning, TEXT("BossRoomClear"));
			//Player = Cast<AFPSPlayer>(_OtherActor);
		m_SequencePlayer->Play();
			
			//if (IsValid(Player))
			//{
			//	Player->SetSeqPlay(true);
			//}

			AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
			if (IsValid(GameMode))
			{
				GameMode->GetMainHUD()->SetVisibility(ESlateVisibility::Hidden);
			}
	}
}

void ABossClearcheckTriggerBox::BeginTrigger(AActor* _TriggerActor, AActor* _OtherActor)
{
	LOG(Monster, Warning, TEXT("Monster Count Plus"));
	MonsterCount += 1;
}

void ABossClearcheckTriggerBox::EndTrigger(AActor* _TriggerActor, AActor* _OtherActor)
{
	LOG(Monster, Warning, TEXT("Monster Death"));
	MonsterCount -= 1;
}

void ABossClearcheckTriggerBox::TeleporterSeqEnd()
{
	AFPSPlayLevelGamemode* GameMode = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(GameMode))
	{
		GameMode->GetMainHUD()->SetVisibility(ESlateVisibility::Visible);
	}

	Destroy();
}
