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
}
