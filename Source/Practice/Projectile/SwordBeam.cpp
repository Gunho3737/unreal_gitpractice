// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBeam.h"

ASwordBeam::ASwordBeam()
	: m_LifeTime(1.5f)
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

	FVector MyLocation = GetActorLocation();

	//���ٴ��� �հ� ������ �ϸ� 0���� ���հ� �ϴ� �ӽñ��
	//���� ������ ���ܼ� �ٴ��� ����� �׷��� �ٴ��� �浹������Ʈ�� overlap������ �ٴڿ� �Ȳ����� �ϵ��� ����
	if (MyLocation.Z <= 0.0f)
	{
		MyLocation.Z = 0.0f;
		SetActorLocation(MyLocation);
	}

	if (m_LifeTime < m_CurTime)
	{
		//����Ʈ ���
		UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());

		// ���� ���
		
		//����

		//���� ����

		//���� �ı�
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
