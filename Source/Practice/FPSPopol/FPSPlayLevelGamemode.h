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

private:
	TSubclassOf<UUserWidget>	m_MainHudClass;
	class UFPS_MainWidget* m_MainHUD;

public:
	class UFPS_MainWidget* GetMainHUD() { return m_MainHUD; }
};
