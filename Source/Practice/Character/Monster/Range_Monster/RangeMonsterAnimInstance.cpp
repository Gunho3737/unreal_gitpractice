// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeMonsterAnimInstance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Monster_Base.h"

void URangeMonsterAnimInstance::NativeInitializeAnimation()
{
	//나를 가진 오너를 저장
	Monster = Cast<AMonster_Base>(TryGetPawnOwner());
}

void URangeMonsterAnimInstance::NativeBeginPlay()
{
	//TSubclassOf를 블루프린트로 로드함
	m_MonBullet = LoadClass<ARangeMonsterBullet>(GetWorld(), TEXT("/Script/Engine.Blueprint'/Game/FPSPopol/Bullet/BPC_RangeMonsterBullet.BPC_RangeMonsterBullet_C'"));
}

void URangeMonsterAnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	//나를 가진 오너가 없을경우 바로 리턴
	if (!IsValid(Monster))
	{
		return;
	}

	//오너의 state를 매번 받아와서 갱신하고 그거에 맞춰 애니메이션 재상
	m_State = Monster->GetState();
}

void URangeMonsterAnimInstance::AnimNotify_RangeMonAtt()
{
	////스폰 액터를 위해 필요한 세팅이 담긴 클래스 param
	FActorSpawnParameters param = {};
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //스폰세팅, 충돌체와 상관없이 지정해준 위치에서 항상 생성
	param.OverrideLevel = Monster->GetLevel();
	param.bDeferConstruction = false;	// 지연생성(BeginPlay 바로호출 X)

	// 카메라 위치 + 카메라 전방방향 * 10미터
	//FVector CamForwardPos = m_Cam->GetComponentLocation() + m_Cam->GetForwardVector() * 1000;

	// 투사체 생성위치, 소켓을 넣어줌
	FVector ProjectileLocation = Monster->GetMesh()->GetSocketLocation(FName(TEXT("Muzzle_01")));

	// 투사체 위치에서 카메라 전방 10미터 위치를 향하는 방향벡터 구하기
	FVector vDir = Monster->GetActorForwardVector();
	vDir.Normalize();

	//투사체의 속도는 전방벡터 5000.f
	AProjectile* pProjectile = GetWorld()->SpawnActor<AProjectile>(m_MonBullet, ProjectileLocation, FRotator(), param);
	pProjectile->m_ProjtileMovement->Velocity = vDir * 1000.f;

	////이펙트 재생하기
	//FVector EffectLocation = GetMesh()->GetSocketLocation(FName(TEXT("Gun_LOS")));
	//FVector EffectLocation = Monster->GetMesh()->GetSocketLocation(FName(TEXT("Muzzle_01")));
	//UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::FIRE, GetLevel(), EffectLocation);
}

void URangeMonsterAnimInstance::AnimNotify_RangeAttEnd()
{
	AAIController* moncon = Cast<AAIController>(Monster->GetController());

	if (moncon != nullptr)
	{
		moncon->GetBlackboardComponent()->SetValueAsBool(FName("IsAttackAnimationPlay"), false);
	}
}
