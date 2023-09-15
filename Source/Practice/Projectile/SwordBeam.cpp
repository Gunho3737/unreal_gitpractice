// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBeam.h"

ASwordBeam::ASwordBeam()
	: m_LifeTime(2.f)
	, m_CurTime(0.f)
{
}

void ASwordBeam::BeginPlay()
{
	Super::BeginPlay();

}

void ASwordBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_CurTime += DeltaTime;

	if (m_LifeTime < m_CurTime)
	{
		//ÀÌÆåÆ® Àç»ý
		UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());

		// »ç¿îµå Àç»ý
		
		//Æø¹ß

		//µ¥´Ô ³²±è

		//ÀÌÈÄ ÆÄ±«
		Destroy();
	}
}

void ASwordBeam::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
}

void ASwordBeam::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
}

void ASwordBeam::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
