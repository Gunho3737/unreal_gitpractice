// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeMonsterBullet.h"
#include "../FPSPopol/Player/FPSPlayer.h"
#include "Components/DecalComponent.h"

void ARangeMonsterBullet::BeginPlay()
{
	Super::BeginPlay();

	//sphere에 충돌 바인딩
	GetSphere()->OnComponentHit.AddDynamic(this, &ARangeMonsterBullet::OnHit);
	GetSphere()->OnComponentBeginOverlap.AddDynamic(this, &ARangeMonsterBullet::BeginOverlap);
	GetSphere()->OnComponentEndOverlap.AddDynamic(this, &ARangeMonsterBullet::EndOverlap);
}

void ARangeMonsterBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_CurTime += DeltaTime;

	if (m_LifeTime < m_CurTime)
	{
		death = true;
	}


	if (death == true)
	{
		Destroy();
	}
}

void ARangeMonsterBullet::BulletDeath()
{
	//GetSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	death = true;
}

ARangeMonsterBullet::ARangeMonsterBullet()
	: m_LifeTime(1.5f)
	, m_CurTime(0.f)
	, death(false)
{

}

ARangeMonsterBullet::~ARangeMonsterBullet()
{
}

void ARangeMonsterBullet::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
	AFPSPlayer* Actor = Cast<AFPSPlayer>(_OtherActor);

	if (IsValid(Actor))
	{
		Actor->HPChange(-21.f);
	}

	BulletDeath();
}

void ARangeMonsterBullet::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
}

void ARangeMonsterBullet::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
