// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonsterAnimInstance.h"
#include "Monster_Base.h"

void UMeleeMonsterAnimInstance::NativeInitializeAnimation()
{
	//���� ���� ���ʸ� ����
	Monster = Cast<AMonster_Base>(TryGetPawnOwner());
}

void UMeleeMonsterAnimInstance::NativeBeginPlay()
{
}

void UMeleeMonsterAnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	//���� ���� ���ʰ� ������� �ٷ� ����
	if (!IsValid(Monster))
	{
		return;
	}
	
	//������ state�� �Ź� �޾ƿͼ� �����ϰ� �װſ� ���� �ִϸ��̼� ���
	m_State = Monster->GetState();
}
