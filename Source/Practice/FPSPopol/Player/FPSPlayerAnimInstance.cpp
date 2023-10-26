// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerAnimInstance.h"

void UFPSPlayerAnimInstance::NativeInitializeAnimation()
{
}

void UFPSPlayerAnimInstance::NativeBeginPlay()
{
	//나(애님인스턴스)를 소유한 액터의 포인터를 받아옴
	Character = Cast<AFPSPlayer>(GetOwningActor());

	if (IsValid(Character))
	{
		//캐릭터의 무브먼트 포인트를 저장해서 애님인스턴스에서 정보를 받아올수 있게함
		Movement = Character->GetCharacterMovement();
	}
}

void UFPSPlayerAnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
}
