// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSPlayLevelGamemode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AFPSPlayLevelGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPSPlayLevelGamemode();
	~AFPSPlayLevelGamemode();

	virtual void BeginPlay() override;
};
