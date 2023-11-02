// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonsterAnimInstance.h"
#include "../Monster_Base.h"
#include "../../../FPSPopol/Player/FPSPlayer.h"

void UMeleeMonsterAnimInstance::NativeInitializeAnimation()
{
	//나를 가진 오너를 저장
	Monster = Cast<AMonster_Base>(TryGetPawnOwner());
}

void UMeleeMonsterAnimInstance::NativeBeginPlay()
{
}

void UMeleeMonsterAnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	//나를 가진 오너가 없을경우 바로 리턴
	if (!IsValid(Monster))
	{
		return;
	}
	
	//오너의 state를 매번 받아와서 갱신하고 그거에 맞춰 애니메이션 재상
	m_State = Monster->GetState();
}

void UMeleeMonsterAnimInstance::AnimNotify_MeleeMonAtt()
{
	//밀리몬스터의 공격 모션에 붙은 노티파이에서 충돌체크


	FHitResult ColResult;
	//내가 세팅해준 세팅값이 들어간 객체

	FVector vec = { 200.f, 200.f, 200.f };

	//스윕 싱글
	bool col = GetWorld()->SweepSingleByChannel(ColResult	//결과값이 들어갈 HitResult
		, Monster->GetActorLocation(), Monster->GetActorLocation()	//충돌체크 시작점과 끝나는 점
		, FQuat::Identity	//기본 사원수값 (1,1,1)
		, ECC_GameTraceChannel7 // Monster Trace Channel
		, FCollisionShape::MakeBox(vec)	//충돌체의 모양듬
	);

	DrawDebugBox(GetWorld(), Monster->GetActorLocation(), vec, FColor::Green, false, 10.f);

	if (col == true)
	{
		AFPSPlayer* pAB = Cast<AFPSPlayer>(ColResult.GetActor());

		if (IsValid(pAB))
		{
			LOG(LogTemp, Warning, TEXT("MeleeMonster Attack Success"));
		}
	}

}
