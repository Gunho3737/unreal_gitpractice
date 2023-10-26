// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../Header/GlobalHeader.h"

#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

UCLASS()
class PRACTICE_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	//�۷ι������ EngineMinimal.h �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* m_Cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* m_Arm;
public:
	// Sets default values for this character's properties
	AFPSPlayer();
	~AFPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
