// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Header/GlobalHeader.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

#include "Projectile.generated.h"

UCLASS()
class PRACTICE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comopnent")
	USphereComponent* m_Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comopnent")
	UProjectileMovementComponent* m_ProjtileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UParticleSystemComponent* m_PSC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UNiagaraComponent* m_NC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* m_Mesh;


public:

	USphereComponent* GetSphere() { return m_Sphere; }

public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
