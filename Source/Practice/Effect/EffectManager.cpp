// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectManager.h"
#include "../PracticeGameModeBase.h"
#include "Effect_Base.h"

//private static 멤버변수
TSharedPtr<UEffectManager> UEffectManager::m_This = nullptr;

UEffectManager* UEffectManager::GetInst()
{
	//싱글톤 객체가 없을시에는 만들어줌
	if (!IsValid(m_This.Get()))
	{
		//c++로 스마트 포인터를 생성함
		m_This = MakeShareable(NewObject<UEffectManager>());
	}

	return m_This.Get();
}


void UEffectManager::CreateEffect(UWorld* _World, EEFFECT_TYPE _Type, ULevel* _Level, FVector _Location)
{
	FActorSpawnParameters param = {};
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	param.OverrideLevel = _Level;
	param.bDeferConstruction = true;	// 지연생성(BeginPlay 호출 X)

	FTransform trans;
	trans.SetLocation(_Location);

	AEffect_Base* pEffect = _World->SpawnActor<AEffect_Base>(AEffect_Base::StaticClass(), trans, param);
	pEffect->SetEffectType(_Type);
	pEffect->FinishSpawning(pEffect->GetTransform());
}