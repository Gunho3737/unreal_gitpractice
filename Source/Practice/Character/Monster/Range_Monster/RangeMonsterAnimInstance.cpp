// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeMonsterAnimInstance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster_Base.h"

void URangeMonsterAnimInstance::NativeInitializeAnimation()
{
	//���� ���� ���ʸ� ����
	Monster = Cast<AMonster_Base>(TryGetPawnOwner());
}

void URangeMonsterAnimInstance::NativeBeginPlay()
{
}

void URangeMonsterAnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	//���� ���� ���ʰ� ������� �ٷ� ����
	if (!IsValid(Monster))
	{
		return;
	}

	//������ state�� �Ź� �޾ƿͼ� �����ϰ� �װſ� ���� �ִϸ��̼� ���
	m_State = Monster->GetState();
}

void URangeMonsterAnimInstance::AnimNotify_RangeMonAtt()
{
}

void URangeMonsterAnimInstance::AnimNotify_RangeAttEnd()
{
	AAIController* moncon = Cast<AAIController>(Monster->GetController());

	if (moncon != nullptr)
	{
		moncon->GetBlackboardComponent()->SetValueAsBool(FName("IsAttackAnimationPlay"), false);
	}
}
