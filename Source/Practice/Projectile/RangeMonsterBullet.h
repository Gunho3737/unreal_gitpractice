// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Sound/SoundCue.h"
#include "../Header/GlobalHeader.h"
#include "RangeMonsterBullet.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API ARangeMonsterBullet : public AProjectile
{
	GENERATED_BODY()

public:
	//소리 재생을 위한 사운드 멤버변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		TSoftObjectPtr<USoundCue>	m_Sound;

	//오브젝트가 살아있을 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		float m_LifeTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BulletDeath();

	ARangeMonsterBullet();
	~ARangeMonsterBullet();

private:
	//델타타임을 계속 더해주고 lifetime과 비교해줄 float
	float m_CurTime;
	bool death;

	// 충돌 관련 Delegate
private:
	//충돌시 호출되는 함수
	UFUNCTION()
		void OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
			, FVector  _vNormalImpulse, const FHitResult& _Hit);
	//오버랩 시작시 호출되는 함수
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
			, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult);
	//오버랩 끝날시 호출 되는 함수
	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
			, int32 _Index);

};
