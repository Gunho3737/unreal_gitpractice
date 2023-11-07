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
	//TSubclassOf�� �������Ʈ�� �ε���
	m_MonBullet = LoadClass<ARangeMonsterBullet>(GetWorld(), TEXT("/Script/Engine.Blueprint'/Game/FPSPopol/Bullet/BPC_RangeMonsterBullet.BPC_RangeMonsterBullet_C'"));
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
	////���� ���͸� ���� �ʿ��� ������ ��� Ŭ���� param
	FActorSpawnParameters param = {};
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //��������, �浹ü�� ������� �������� ��ġ���� �׻� ����
	param.OverrideLevel = Monster->GetLevel();
	param.bDeferConstruction = false;	// ��������(BeginPlay �ٷ�ȣ�� X)

	// ī�޶� ��ġ + ī�޶� ������� * 10����
	//FVector CamForwardPos = m_Cam->GetComponentLocation() + m_Cam->GetForwardVector() * 1000;

	// ����ü ������ġ, ������ �־���
	FVector ProjectileLocation = Monster->GetMesh()->GetSocketLocation(FName(TEXT("Muzzle_01")));

	// ����ü ��ġ���� ī�޶� ���� 10���� ��ġ�� ���ϴ� ���⺤�� ���ϱ�
	FVector vDir = Monster->GetActorForwardVector();
	vDir.Normalize();

	//����ü�� �ӵ��� ���溤�� 5000.f
	AProjectile* pProjectile = GetWorld()->SpawnActor<AProjectile>(m_MonBullet, ProjectileLocation, FRotator(), param);
	pProjectile->m_ProjtileMovement->Velocity = vDir * 1000.f;

	////����Ʈ ����ϱ�
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
