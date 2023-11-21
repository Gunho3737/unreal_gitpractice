// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Header/GlobalHeader.h"
#include "GameEndPortalActor.generated.h"

UCLASS()
class PRACTICE_API AGameEndPortalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameEndPortalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UParticleSystemComponent* m_PSC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* m_Box;
};
