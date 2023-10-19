// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_AnimInstance.h"
#include "../Material/PhysicMT/MyLandScapePhysicalMaterial.h"

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

void UCharacter_AnimInstance::AnimNotify_LFootStomp()
{
	LOG(LogTemp, Warning, TEXT("LFootStompCall"));
	PlayPhysicalBasedSound(TEXT("Foot_L"));
}

void UCharacter_AnimInstance::AnimNotify_RFootStomp()
{
	LOG(LogTemp, Warning, TEXT("RFootStompCall"));
	PlayPhysicalBasedSound(TEXT("Foot_R"));
}

void UCharacter_AnimInstance::PlayPhysicalBasedSound(const FString& _strSockName)
{
	ACharacter_Base* pPlayer = Cast<ACharacter_Base>(TryGetPawnOwner());
	if (!IsValid(pPlayer))
		return;

	FVector vSockStartPos = pPlayer->GetMesh()->GetSocketLocation(*_strSockName);
	FVector vSockEndPos = vSockStartPos + FVector(0.f, 0.f, -100.f);

	// 충돌 결과를 받을 Result 구조체
	FHitResult hitresult = {};

	// 충돌 옵션 설정 Parameter 구조체
	FCollisionQueryParams param = {};
	param.bReturnPhysicalMaterial = true;	// Trace 충돌 성공 시, 해당 물체의 물리재질 받아오기 옵션
	param.AddIgnoredActor(pPlayer);			// Trace 무시할 액터 등록

	// LineTrace 진행, ECC_GameTraceChannel6 는 Trace_Landscae 채널
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitresult, vSockStartPos, vSockEndPos, ECC_GameTraceChannel6, param);


	if (bHit)
	{
		// 충돌 결과 물리재질을 UPhysicalMaterial_Landscape 로 캐스팅
		UMyLandScapePhysicalMaterial* pPMT = Cast<UMyLandScapePhysicalMaterial>(hitresult.PhysMaterial);
		if (!IsValid(pPMT))
			return;

		//pPMT->GetParticle();
		//pPMT->GetNiagara();

		USoundBase* pSound = pPMT->GetSound();
		if (IsValid(pSound))
		{
			// hitresult.ImpactPoint;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pSound, vSockStartPos);
		}
	}

}
