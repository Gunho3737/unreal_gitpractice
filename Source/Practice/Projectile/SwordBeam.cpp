// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordBeam.h"

#include "Components/DecalComponent.h"
#include "../Character/Monster/Monster_Base.h"

ASwordBeam::ASwordBeam()
	: m_LifeTime(1.5f)
	, m_CurTime(0.f)
	, death(false)
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

	//sphere�� �浹 ���ε�
	GetSphere()->OnComponentHit.AddDynamic(this, &ASwordBeam::OnHit);
	GetSphere()->OnComponentBeginOverlap.AddDynamic(this, &ASwordBeam::BeginOverlap);
	GetSphere()->OnComponentEndOverlap.AddDynamic(this, &ASwordBeam::EndOverlap);
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
		death = true;
	}

	if (death == true)
	{
		//����Ʈ ���
		UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());

		// ���� ���
		if (false == m_Sound.IsNull())
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_Sound.LoadSynchronous(), GetActorLocation());
		}

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
	AMonster_Base* pMonster = Cast<AMonster_Base>(_OtherActor);

	if (IsValid(pMonster))
	{
		//���� �浹 ����� ���͸� ��� ���� Ʈ���Ÿ� �ߵ�
		death = true;
	}

}

void ASwordBeam::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
