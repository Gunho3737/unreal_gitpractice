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
	//틱마다실행

	if (!IsValid(Character) || !IsValid(Movement))
	{
		//캐릭터와 무브먼트가 없으면 리턴
		return;
	}

	//속력을 받아와서
	MoveSpeed = Movement->Velocity.Size2D();

	//속력, 가속도 상태를 체크해서 현재 이동상태를 정해줌
	if (0.f < MoveSpeed && !Movement->GetCurrentAcceleration().IsZero())
	{
		IsMove = true;
	}
	else
	{
		IsMove = false;
	}

	//회전값받아온 다음 
	FRotator Rot = Character->GetRootComponent()->GetRelativeRotation();
	LocalVelocity = Rot.UnrotateVector(Movement->Velocity);

	//현재 공격여부에 따라 공격애니메이션 가중치를 정해줌
	if (IsAttack == false)
	{
		AttackWeight = 0.f;
	}
	else if (IsAttack == true)
	{
		AttackWeight = 1.f;
	}

	// 카메라 LookAt 위치 계산
	Character->GetActorLocation();
	Character->GetActorForwardVector();

	CameraLookAt = Character->m_Cam->GetComponentLocation() + Character->m_Cam->GetForwardVector() * 500;
}
