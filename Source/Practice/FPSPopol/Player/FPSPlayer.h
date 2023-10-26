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
	//글로벌헤더의 EngineMinimal.h 사용중
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* m_Cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* m_Arm;

private:
	//매핑 컨텍스트
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext>	InputMapping;

	//인풋액션
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			RotationAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction>			AttackAction;

public:
	// Sets default values for this character's properties
	AFPSPlayer();
	~AFPSPlayer();

public:
	void Move(const FInputActionInstance& _Instance);
	void Rotation(const FInputActionInstance& _Instance);
	void Jump(const FInputActionInstance& _Instance);
	void Attack(const FInputActionInstance& _Instance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
