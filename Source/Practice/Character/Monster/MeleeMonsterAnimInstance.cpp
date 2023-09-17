// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonsterAnimInstance.h"
#include "Monster_Base.h"

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
