// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../../Header/GlobalHeader.h"
#include "RangeMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API URangeMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//오너를 받아옴
	class AMonster_Base* Monster;

	//Enum별 애니메이션을 위해 멤버변수로 EnumState를 가지고 있음
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	EMON_STATE			 m_State;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float _fDeltaTime) override;

public:
	UFUNCTION()
	void AnimNotify_RangeMonAtt();
	
	UFUNCTION()
	void AnimNotify_RangeAttEnd();
};
