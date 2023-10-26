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

	//�÷��̾��� ������ �������� �ִϸ��̼��� �����ϱ� ������ ������ �÷��̾ �����ͷ� ��� ����
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "�������")
	AFPSPlayer* Character;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "������Ʈ")
	UCharacterMovementComponent* Movement;

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float _fDeltaTime) override;
};
