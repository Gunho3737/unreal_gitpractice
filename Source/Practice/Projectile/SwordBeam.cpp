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

	//sphere에 충돌 바인딩
	GetSphere()->OnComponentHit.AddDynamic(this, &ASwordBeam::OnHit);
	GetSphere()->OnComponentBeginOverlap.AddDynamic(this, &ASwordBeam::BeginOverlap);
	GetSphere()->OnComponentEndOverlap.AddDynamic(this, &ASwordBeam::EndOverlap);
}

void ASwordBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_CurTime += DeltaTime;

	FVector MyLocation = GetActorLocation();

	//땅바닥을 뚫고 들어가려고 하면 0으로 못뚫게 하는 임시기능
	//후일 지형이 생겨서 바닥이 생기고 그러면 바닥의 충돌컴포넌트와 overlap했을때 바닥에 안꺼지게 하도록 구현
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
		//이펙트 재생
		UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());

		// 사운드 재생
		if (false == m_Sound.IsNull())
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_Sound.LoadSynchronous(), GetActorLocation());
		}

		// 투사체 Z좌표가 10.f이상이면 데칼 남김
		if (MyLocation.Z <= 10.0f)
		{
			FActorSpawnParameters param = {};
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //스폰세팅, 충돌체와 상관없이 지정해준 위치에서 항상 생성
			param.OverrideLevel = GetLevel();
			param.bDeferConstruction = false;	// 지연생성(BeginPlay 바로호출 X)
			ASwordBeamCrackDecal* CrackDecal = GetWorld()->SpawnActor<ASwordBeamCrackDecal>(SwordBeamDecal, GetActorLocation(), FRotator(), param);
			CrackDecal->GetDecal()->SetFadeOut(0.5f, 3.0f, true);
		}

		//이후 파괴
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
		//만약 충돌 대상이 몬스터면 즉시 폭발 트리거를 발동
		death = true;
	}

}

void ASwordBeam::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
}
