// Copyright Epic Games, Inc. All Rights Reserved.


#include "PracticeGameModeBase.h"

APracticeGameModeBase::APracticeGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> Finder(TEXT("/Script/Engine.Blueprint'/Game/MyCharacter/Character/BPC_Grey.BPC_Grey_C'"));
	if (Finder.Succeeded())
	{
		DefaultPawnClass = Finder.Class;
	}
}

APracticeGameModeBase::~APracticeGameModeBase()
{
	//if (nullptr != m_EffectMgr)
	//{
	//	m_EffectMgr->ConditionalBeginDestroy();
	//}
}