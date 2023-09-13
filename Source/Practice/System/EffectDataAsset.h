// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Header/GlobalHeader.h"

#include "EffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UEffectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//이펙트 세팅을 위한 데이터 에셋
	UPROPERTY(EditDefaultsOnly, Category = "Effect", meta = (DisplayName = "Effect 와 파티클 세팅"))
	TArray<FEffectData>							EffectDataArr;
};
