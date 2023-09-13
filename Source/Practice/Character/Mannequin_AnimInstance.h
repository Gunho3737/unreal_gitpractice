// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Mannequin_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMannequin_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// �ʱ�ȭ
	virtual void NativeInitializeAnimation() override;

	// ���忡 ���� ������ ȣ��
	virtual void NativeBeginPlay() override;

	// �� ƽ(������) ���� ȣ��
	virtual void NativeUpdateAnimation(float _fDeltaTime) override;
	
};
