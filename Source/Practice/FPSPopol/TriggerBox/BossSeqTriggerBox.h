// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "../../Header/GlobalHeader.h"

#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"

#include "BossSeqTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API ABossSeqTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32			m_PlayCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ULevelSequence* m_LvSeq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool			HideHUD;


	ULevelSequencePlayer* m_SequencePlayer;
	ALevelSequenceActor* m_SequenceActor;

	class AFPSPlayer* Player;

public:
	ABossSeqTriggerBox();

	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginTrigger(AActor* _TriggerActor, AActor* _OtherActor);

	UFUNCTION()
	void EndTrigger(AActor* _TriggerActor, AActor* _OtherActor);

	UFUNCTION()
	void BossSeqEnd();

};
