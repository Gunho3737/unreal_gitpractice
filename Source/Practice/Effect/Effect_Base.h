// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Header/GlobalHeader.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "../System/EffectDataAsset.h"


#include "Effect_Base.generated.h"

UCLASS()
class PRACTICE_API AEffect_Base : public AActor
{
	GENERATED_BODY()

public:
	//파티클의 Root 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* m_Root;

	//파티클 시스템 컴포넌트
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Component")
	UParticleSystemComponent* m_PSC;
	
	//나이아가라 컴포넌트
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Component")
	UNiagaraComponent* m_NC;

	//효과가 무슨효과인지 정하는 ENUM
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	EEFFECT_TYPE						Type;
	
	//이펙트세팅을 저장해둔 데이터 에셋
	UPROPERTY(EditAnywhere, Category = "Info")
	TSoftObjectPtr<UEffectDataAsset>	EffectSetting;

public:	
	// Sets default values for this actor's properties
	AEffect_Base();

public:
	//타입을 세팅하는 함수
	void SetEffectType(EEFFECT_TYPE _Type) { Type = _Type; }

	//호출시 객체가 파괴되는 함수
	UFUNCTION()
	void OnFinished(UParticleSystemComponent* _PSC);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
