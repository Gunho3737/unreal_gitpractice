// Fill out your copyright notice in the Description page of Project Settings.


#include "BossClearcheckTriggerBox.h"

ABossClearcheckTriggerBox::ABossClearcheckTriggerBox()
	: MonsterCount(0)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossClearcheckTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	//���� �� Ʈ���� �ڽ��� ���Ͷ��� ��ġ����
	OnActorBeginOverlap.AddDynamic(this, &ABossClearcheckTriggerBox::BeginTrigger);
	OnActorEndOverlap.AddDynamic(this, &ABossClearcheckTriggerBox::EndTrigger);
}

void ABossClearcheckTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//LOG(Monster, Warning, TEXT("BossFight Activate"));

	if (MonsterCount == 0) 
	{
		LOG(Monster, Warning, TEXT("BossRoomClear"));
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
