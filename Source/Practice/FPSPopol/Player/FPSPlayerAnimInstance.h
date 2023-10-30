// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Header/GlobalHeader.h"
#include "FPSPlayer.h"
#include "Animation/AnimInstance.h"
#include "FPSPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UFPSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	//플레이어의 정보를 바탕으로 애니메이션을 변경하기 때문에 오너인 플레이어를 포인터로 들고 있음
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "member")
	AFPSPlayer* Character;

	//플레이어의 무브먼트
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Component")
	UCharacterMovementComponent* Movement;

	//플레이어의 속도값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	FVector		LocalVelocity;

	//카메라가 바라보고 있는 방향벡터 LookAt값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	FVector CameraLookAt;

	//플레이어의 속력값, 속력은 속도랑 다르게 방향은 빠져있음
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	float		MoveSpeed;

	//현재 이동중인지 체크할 bool값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Data")
	bool		IsMove;

	//현재 공격여부를 체크하는 bool값
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	bool		IsAttack;

	//공격모션 몽타쥬를 위한 가중치 float
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "데이터")
	float	 AttackWeight;
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float _fDeltaTime) override;

	UFUNCTION()
	void AnimNotify_ShootStart();

	UFUNCTION()
	void AnimNotify_ShootEnd();

	UFUNCTION()
	void AnimNotify_ReloadStart();

	UFUNCTION()
	void AnimNotify_ReloadEnd();
};
