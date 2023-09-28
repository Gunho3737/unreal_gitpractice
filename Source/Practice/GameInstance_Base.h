// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Header/GlobalHeader.h"
#include "GameInstance_Base.generated.h"

class UInventoryManager;

UCLASS()
class PRACTICE_API UGameInstance_Base : public UGameInstance
{
	GENERATED_BODY()

private:
	UInventoryManager* m_InvenMgr;

public:
	UGameInstance_Base();
	~UGameInstance_Base();

	friend class UInventoryManager;
};
