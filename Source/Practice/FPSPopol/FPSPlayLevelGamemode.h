// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlayerUI/FPS_MainWidget.h"
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
	UFPS_MainWidget* m_MainHUD;

public:
	UFPS_MainWidget* GetMainHUD() { return m_MainHUD; }
};
