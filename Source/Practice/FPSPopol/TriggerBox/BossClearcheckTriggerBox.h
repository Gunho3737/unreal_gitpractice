// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "../../Header/GlobalHeader.h"

#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"

#include "BossClearcheckTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API ABossClearcheckTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ULevelSequence* m_LvSeq;

	ULevelSequencePlayer* m_SequencePlayer;
	ALevelSequenceActor* m_SequenceActor;

	int MonsterCount;

public:
	ABossClearcheckTriggerBox();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginTrigger(AActor* _TriggerActor, AActor* _OtherActor);

	UFUNCTION()
	void EndTrigger(AActor* _TriggerActor, AActor* _OtherActor);

};
