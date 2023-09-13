// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Header/GlobalHeader.h"

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IA_DataAsset.generated.h"

UCLASS()
class PRACTICE_API UIA_DataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	//인풋정보들을 저장할 동적배열(TArray)를 가진 데이터 에셋
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "InputAction 입력"))
	TArray<FIAData>	IADataArr;
};
