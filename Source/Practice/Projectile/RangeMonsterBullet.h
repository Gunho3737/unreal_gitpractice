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
	//�Ҹ� ����� ���� ���� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		TSoftObjectPtr<USoundCue>	m_Sound;

	//������Ʈ�� ������� �ð�
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
	//��ŸŸ���� ��� �����ְ� lifetime�� ������ float
	float m_CurTime;
	bool death;

	// �浹 ���� Delegate
private:
	//�浹�� ȣ��Ǵ� �Լ�
	UFUNCTION()
		void OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
			, FVector  _vNormalImpulse, const FHitResult& _Hit);
	//������ ���۽� ȣ��Ǵ� �Լ�
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
			, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult);
	//������ ������ ȣ�� �Ǵ� �Լ�
	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
			, int32 _Index);

};
