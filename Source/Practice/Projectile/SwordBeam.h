// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Header/GlobalHeader.h"

#include "CoreMinimal.h"
#include "Projectile.h"
#include "../Effect/EffectManager.h"
#include "SwordBeam.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API ASwordBeam : public AProjectile
{
	GENERATED_BODY()
	
public:
	//������Ʈ�� ������� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	float m_LifeTime;

private:
	//��ŸŸ���� ��� �����ְ� lifetime�� ������ float
	float m_CurTime;

public:
	// Sets default values for this actor's properties
	ASwordBeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
