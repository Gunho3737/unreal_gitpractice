// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AStartLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TSubclassOf<UUserWidget>	m_MainHudClass;

	class UStartMenuWidget* m_MainHUD;
	
public:
	AStartLevelGameMode();
	~AStartLevelGameMode();

public:
	virtual void BeginPlay() override;
	
};
