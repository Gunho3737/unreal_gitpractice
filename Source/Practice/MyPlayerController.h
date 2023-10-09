// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float _DT) override;
	virtual void BeginPlay() override;

public:
	AMyPlayerController();
};
