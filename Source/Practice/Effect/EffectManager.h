// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Header/GlobalHeader.h"
#include "UObject/NoExportTypes.h"

#include "EffectManager.generated.h"

// 싱글톤 클래스는 어디에 부착하지 않고 UOBJECT 매크로를 선택할시
// 가비지 컬렉터에서 날아갈 위험이 크므로 순수 c++로 만 사용하게 해야한다
UCLASS()
class PRACTICE_API UEffectManager : public UObject
{
	GENERATED_BODY()

private:
	// 데이터 영역
	// 나 자신의 포인터를 private로 가지고 있으면서
	// 스태틱으로 선언해 메모리 영역에 할당함
	//언리얼 스마트 포인터 TSharedPtr
	static TSharedPtr<UEffectManager>	m_This;

public:
	static UEffectManager* GetInst();

	UFUNCTION(BlueprintCallable)
	void CreateEffect(UWorld* _World, EEFFECT_TYPE _Type, ULevel* _Level, FVector _Location);

	//기존 이펙트 생성에서 Rotate도 넣으면 쓸수있도록 오버라이드
	void CreateEffect(UWorld* _World, EEFFECT_TYPE _Type, ULevel* _Level, FRotator _Rotate, FVector _Location);
};
