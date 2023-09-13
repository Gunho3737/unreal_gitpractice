// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Effect/EffectManager.h"
#include "GameFramework/GameModeBase.h"
#include "PracticeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API APracticeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	//이펙트 매니져를 싱글톤화
	//UEffectManager* m_EffectMgr;
	//friend class UEffectManager;
public:
	APracticeGameModeBase();
	~APracticeGameModeBase();

};
