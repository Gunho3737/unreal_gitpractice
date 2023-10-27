// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerAnimInstance.h"

void UFPSPlayerAnimInstance::NativeInitializeAnimation()
{
}

void UFPSPlayerAnimInstance::NativeBeginPlay()
{
	//��(�ִ��ν��Ͻ�)�� ������ ������ �����͸� �޾ƿ�
	Character = Cast<AFPSPlayer>(GetOwningActor());

	if (IsValid(Character))
	{
		//ĳ������ �����Ʈ ����Ʈ�� �����ؼ� �ִ��ν��Ͻ����� ������ �޾ƿü� �ְ���
		Movement = Character->GetCharacterMovement();
	}
}

void UFPSPlayerAnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	//ƽ���ٽ���

	if (!IsValid(Character) || !IsValid(Movement))
	{
		//ĳ���Ϳ� �����Ʈ�� ������ ����
		return;
	}

	//�ӷ��� �޾ƿͼ�
	MoveSpeed = Movement->Velocity.Size2D();

	//�ӷ�, ���ӵ� ���¸� üũ�ؼ� ���� �̵����¸� ������
	if (0.f < MoveSpeed && !Movement->GetCurrentAcceleration().IsZero())
	{
		IsMove = true;
	}
	else
	{
		IsMove = false;
	}

	//ȸ�����޾ƿ� ���� 
	FRotator Rot = Character->GetRootComponent()->GetRelativeRotation();
	LocalVelocity = Rot.UnrotateVector(Movement->Velocity);

	//���� ���ݿ��ο� ���� ���ݾִϸ��̼� ����ġ�� ������
	if (IsAttack == false)
	{
		AttackWeight = 0.f;
	}
	else if (IsAttack == true)
	{
		AttackWeight = 1.f;
	}

	// ī�޶� LookAt ��ġ ���
	Character->GetActorLocation();
	Character->GetActorForwardVector();

	CameraLookAt = Character->m_Cam->GetComponentLocation() + Character->m_Cam->GetForwardVector() * 500;
}
