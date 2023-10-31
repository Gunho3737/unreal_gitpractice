// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::Tick(float DeltaTime)
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

void ABullet::BulletDeath()
{
	death = true;
}

ABullet::ABullet()
	: m_LifeTime(1.5f)
	, m_CurTime(0.f)
	, death(false)
{
}

ABullet::~ABullet()
{
}

void ABullet::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
}

void ABullet::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
}

void ABullet::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
