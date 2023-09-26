// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InvenItemData.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UInvenItemData : public UObject
{
	GENERATED_BODY()

private:
	//�����ۿ� ����� �������� �ּ�
	FString		m_IconImgPath;
	//�������� �̸�
	FString		m_ItemName;
	//�������� ����
	FString		m_Description;
	//�����ϰ� �ִ� ���� �������� ����
	int32		m_Count;

public:
	void SetIconImgPath(const FString& _Path) { m_IconImgPath = _Path; }
	const FString& GetIconImgPath() { return m_IconImgPath; }

	void SetItemName(const FString& _Name) { m_ItemName = _Name; }
	const FString& GetItemName() { return m_ItemName; }

	void SetItemDescription(const FString& _Name) { m_Description = _Name; }
	const FString& GetItemDescription() { return m_Description; }

	void SetItemCount(int32 _Count) { m_Count = _Count; }
	int32 GetItemCount() { return m_Count; }

public:
	UInvenItemData();
	~UInvenItemData();
};
