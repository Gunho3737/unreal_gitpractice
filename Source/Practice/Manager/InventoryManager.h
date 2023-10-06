// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Header/GlobalHeader.h"
#include "InventoryManager.generated.h"



USTRUCT()
struct FItemStack
{
	GENERATED_BODY();

	FGameItemInfo* ItemInfo;
	int32			Stack;
};



/**
 * 
 */
UCLASS()
class PRACTICE_API UInventoryManager : public UObject
{
	GENERATED_BODY()

private:
	static UWorld* m_World;

private:
	// ������ ������ ���̺�
	UDataTable* m_ItemTable;

	// ������ ����
	TMap<EITEM_ID, FGameItemInfo>	m_mapItemInfo;

	// ���� ������
	TMap<EITEM_ID, FItemStack>		m_BackPack[(int32)EITEM_TYPE::END];

public:
	static UInventoryManager* GetInst(UWorld* _World);

	UFUNCTION(BlueprintCallable)
	static UInventoryManager* GetInst(UGameInstance* _GameInst);

	void SetGameItemDataTable(UDataTable* _ItemDataTable);
	void AddGameItem(EITEM_ID _ID);

	void OpenInventoryUI();

	//UMG�ʿ��� ȣ���Ű�� �ϱ� ���� blueprintcallable
	UFUNCTION(BlueprintCallable)
	void CloseInventoryUI();

private:
	void ResetWidget();
	
};
