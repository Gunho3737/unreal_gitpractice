// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBeam.h"

ASwordBeam::ASwordBeam()
	: m_LifeTime(1.f)
	, m_CurTime(0.f)
{
}

void ASwordBeam::BeginPlay()
{
	Super::BeginPlay();
	//UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());
}

void ASwordBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_CurTime += DeltaTime;

	if (m_LifeTime < m_CurTime)
	{
		//ÀÌÆåÆ® Àç»ý

		// »ç¿îµå Àç»ý
		
		//Æø¹ß

		//µ¥´Ô ³²±è

		//ÀÌÈÄ ÆÄ±«
		Destroy();
	}
}
