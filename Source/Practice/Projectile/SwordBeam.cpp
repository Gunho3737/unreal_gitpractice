// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBeam.h"
#include "Components/DecalComponent.h"

ASwordBeam::ASwordBeam()
	: m_LifeTime(1.5f)
	, m_CurTime(0.f)
{
	ConstructorHelpers::FClassFinder<ASwordBeamCrackDecal> SwordBeam(TEXT("/Script/Engine.Blueprint'/Game/MyCharacter/Projectile/BPC_SwordBeamGroundCrack.BPC_SwordBeamGroundCrack_C'"));
	if (SwordBeam.Succeeded())
	{
		SwordBeamDecal = SwordBeam.Class;
	}
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

		// ����ü Z��ǥ�� 10.f�̻��̸� ��Į ����
		if (MyLocation.Z <= 10.0f)
		{
			FActorSpawnParameters param = {};
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //��������, �浹ü�� ������� �������� ��ġ���� �׻� ����
			param.OverrideLevel = GetLevel();
			param.bDeferConstruction = false;	// ��������(BeginPlay �ٷ�ȣ�� X)
			ASwordBeamCrackDecal* CrackDecal = GetWorld()->SpawnActor<ASwordBeamCrackDecal>(SwordBeamDecal, GetActorLocation(), FRotator(), param);
			CrackDecal->GetDecal()->SetFadeOut(0.5f, 3.0f, true);
		}

		//���� �ı�
		Destroy();
	}
}

void ASwordBeam::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
}

void ASwordBeam::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
	//���� ��ģ ����� ���͸� m_LifeTime�� 0���� ���� ��� ���߽�Ŵ
}

void ASwordBeam::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
