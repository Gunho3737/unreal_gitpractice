// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/DecalComponent.h"

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//sphere에 충돌 바인딩
	GetSphere()->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	GetSphere()->OnComponentBeginOverlap.AddDynamic(this, &ABullet::BeginOverlap);
	GetSphere()->OnComponentEndOverlap.AddDynamic(this, &ABullet::EndOverlap);
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
	GetSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//death = true;
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
	//LOG(LogTemp, Warning, TEXT("BulletBlock"));
	GetSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//death = true;
}

void ABullet::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
}

void ABullet::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
