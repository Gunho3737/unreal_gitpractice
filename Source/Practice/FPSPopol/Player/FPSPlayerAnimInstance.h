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
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "멤버변수")
	AFPSPlayer* Character;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "컴포넌트")
	UCharacterMovementComponent* Movement;

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float _fDeltaTime) override;
};
