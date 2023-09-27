// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "../GameInstance_Base.h"

UWorld* UInventoryManager::m_World = nullptr;

UInventoryManager* UInventoryManager::GetInst(UWorld* _World)
{
	return nullptr;
}

UInventoryManager* UInventoryManager::GetInst(UGameInstance* _GameInst)
{
	return nullptr;
}

void UInventoryManager::SetGameItemDataTable(UDataTable* _ItemDataTable)
{
}

void UInventoryManager::AddGameItem(EITEM_ID _ID)
{
}

void UInventoryManager::OpenInventoryUI()
{
}

void UInventoryManager::CloseInventoryUI()
{
}

void UInventoryManager::ResetWidget()
{
}
