// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "../../Header/GlobalHeader.h"

#include "SwordBeamCrackDecal.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API ASwordBeamCrackDecal : public ADecalActor
{
	GENERATED_BODY()
	
public:
	ASwordBeamCrackDecal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
