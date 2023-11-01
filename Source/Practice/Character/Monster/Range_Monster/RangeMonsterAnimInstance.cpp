// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeMonsterAnimInstance.h"
#include "../Monster_Base.h"

void URangeMonsterAnimInstance::NativeInitializeAnimation()
{
	//나를 가진 오너를 저장
	Monster = Cast<AMonster_Base>(TryGetPawnOwner());
}

void URangeMonsterAnimInstance::NativeBeginPlay()
{
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
