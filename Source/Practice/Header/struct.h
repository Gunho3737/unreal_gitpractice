#pragma once

#include "enum.h"
#include "InputAction.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"
#include "Engine/Datatable.h"


#include "struct.generated.h"

//언리얼 구조체 선언에 필요한 매크로
USTRUCT(Atomic, BlueprintType)
struct FIAData	//구조체명에는 F를 붙히는것으로 명확하게 함
{
	//인풋 데이터 에셋을 위한 구조체

	//구조체, 클래스의 선언에 필수적으로 필요한 매크로
	GENERATED_BODY()

public:
	//액션enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInputActionType				Type;
	//실제인풋액션을 softobjectptr로 약한참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UInputAction>	Action;
};

//
USTRUCT(Atomic, BlueprintType)
struct FEffectData
{
	//이펙트 데이터 에셋을 위한 구조체

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEFFECT_TYPE		Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UParticleSystem>	Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UNiagaraSystem>	Niagara;
};

USTRUCT(Atomic, BlueprintType)
struct FMonsterInfo : public FTableRowBase	//#include "Engine/Datatable.h"
{
	//몬스터의 정보가 담길 구조체

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Att;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;
};