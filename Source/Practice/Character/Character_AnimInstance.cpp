// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_AnimInstance.h"

void UCharacter_AnimInstance::NativeInitializeAnimation()
{
}

void UCharacter_AnimInstance::NativeBeginPlay()
{
	//���� ������ Actor�� ĳ���ͷ� �ٿ�ĳ��Ʈ��
	Character = Cast<ACharacter_Base>(GetOwningActor());

	if (IsValid(Character))
	{
		//movement�� ������ ����
		Movement = Character->GetCharacterMovement();
	}

	//발 소켓 Foot_L, Foot_R
}

void UCharacter_AnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	if (!IsValid(Character) || !IsValid(Movement))
		return;

	// �ӷ� üũ
	MoveSpeed = Movement->Velocity.Size2D();

	// �����̰� �ִ��� üũ
	if (0.f < MoveSpeed && !Movement->GetCurrentAcceleration().IsZero())
	{
		IsMove = true;
	}
	else
	{
		IsMove = false;
	}

	
	FRotator Rot = Character->GetRootComponent()->GetRelativeRotation();
	LocalVelocity = Rot.UnrotateVector(Movement->Velocity);

	// ���� �ִ��� ���߿� ���ִ��� üũ
	IsFall = Movement->IsFalling();

	//현재 공격중이 아니며, 애니메이션 역시 재생중이 아니어야 애니메이션이 꺼진다
	if (IsAttack == false)
	{
		AttackWeight = 0.f;
	}
	else if (IsAttack == true)
	{
		AttackWeight = 1.f;
	}

	// 카메라 LookAt 위치 계산
	//컴포넌트의 위치 + 카메라의 1000f앞 전방벡터
	CameraLookAt = Character->m_Cam->GetComponentLocation() + Character->m_Cam->GetForwardVector() * 1000;
}

void UCharacter_AnimInstance::AnimNotify_AttStart()
{
	UE_LOG(LogTemp, Warning, TEXT("AttStart_Call"));
	IsAttack = true;
}

void UCharacter_AnimInstance::AnimNotify_AttComboCheck()
{
	Character->IsCombo = true;
}

void UCharacter_AnimInstance::AnimNotify_AttEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("AttEnd_Call"));

	IsAttack = false;

	if (Character->IsCombo == true)
	{
		Character->IsCombo = false;
		IsAttack = true;
	//	Montage_JumpToSection("ComboStart", Character->GetAttackMontage().LoadSynchronous());
	}
	else
	{
		Character->IsCombo = false;
		Montage_Stop(0.2f);
	}

	return;
	
}

void UCharacter_AnimInstance::AnimNotify_ComboStart()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboStart_Call"));
	IsAttack = true;
}

void UCharacter_AnimInstance::AnimNotify_ComboEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("ComboEnd_Call"));

	IsAttack = false;
	Montage_Stop(0.2f);
}
