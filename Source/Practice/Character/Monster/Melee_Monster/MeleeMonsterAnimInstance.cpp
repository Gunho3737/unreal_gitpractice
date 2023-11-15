// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeMonsterAnimInstance.h"
#include "../Monster_Base.h"
#include "../../../FPSPopol/Player/FPSPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void UMeleeMonsterAnimInstance::AnimNotify_MeleeMonAtt()
{
	//�и������� ���� ��ǿ� ���� ��Ƽ���̿��� �浹üũ


	FHitResult ColResult;
	//���� �������� ���ð��� �� ��ü

	FVector vec = { 170.f, 170.f, 170.f };

	//���� �̱�
	bool col = GetWorld()->SweepSingleByChannel(ColResult	//������� �� HitResult
		, Monster->GetActorLocation(), Monster->GetActorLocation()	//�浹üũ �������� ������ ��
		, FQuat::Identity	//�⺻ ������� (1,1,1)
		, ECC_GameTraceChannel7 // Monster Trace Channel
		, FCollisionShape::MakeBox(vec)	//�浹ü�� ����
	);

	//DrawDebugBox(GetWorld(), Monster->GetActorLocation(), vec, FColor::Green, false, 3.f);

	if (col == true)
	{
		AFPSPlayer* pAB = Cast<AFPSPlayer>(ColResult.GetActor());

		if (IsValid(pAB))
		{
			LOG(LogTemp, Warning, TEXT("MeleeMonster Attack Success"));
			pAB->HPChange(-10.f);
		}
	}

}

void UMeleeMonsterAnimInstance::AnimNotify_MeleeAttEnd()
{
	AAIController* moncon = Cast<AAIController>(Monster->GetController());

	if (moncon != nullptr)
	{
		moncon->GetBlackboardComponent()->SetValueAsBool(FName("IsAttackAnimationPlay"), false);
	}
}
