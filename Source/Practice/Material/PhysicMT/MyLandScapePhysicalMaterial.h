// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Header/GlobalHeader.h"
#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "MyLandScapePhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UMyLandScapePhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundBase* m_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* m_Niagara;

public:
	void SetSound(USoundBase* _Sound) { m_Sound = _Sound; }
	void SetParticle(UParticleSystem* _Particle) { m_Particle = _Particle; }
	void SetNiagara(UNiagaraSystem* _Niagara) { m_Niagara = _Niagara; }

	USoundBase* GetSound() { return m_Sound; }
	UParticleSystem* GetParticle() { return m_Particle; }
	UNiagaraSystem* GetNiagara() { return m_Niagara; }
};
