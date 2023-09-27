// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "../GameInstance_Base.h"

#include "../PracticeGameModeBase.h"
#include "../UI/MainHUDWidget.h"
#include "../UI/Inventory_Base.h"
#include "../System/InvenItemData.h"


UWorld* UInventoryManager::m_World = nullptr;

UInventoryManager* UInventoryManager::GetInst(UWorld* _World)
{
	m_World = _World;

	return GetInst(m_World->GetGameInstance());
}

UInventoryManager* UInventoryManager::GetInst(UGameInstance* _GameInst)
{
	UGameInstance_Base* pGameInst = Cast<UGameInstance_Base>(_GameInst);

	if (!IsValid(pGameInst->m_InvenMgr))
	{
		pGameInst->m_InvenMgr = NewObject<UInventoryManager>();
		pGameInst->m_InvenMgr->AddToRoot();
	}

	return pGameInst->m_InvenMgr;
}

void UInventoryManager::SetGameItemDataTable(UDataTable* _ItemDataTable)
{
	m_ItemTable = _ItemDataTable;

	// 데이터 테이블 안에있는 모든 정보를 TArray 에 넣는다.
	FString str;
	TArray<FGameItemInfo*>	arrTableData;
	m_ItemTable->GetAllRows<FGameItemInfo>(str, arrTableData);

	// 테이블 안에 있는 아이템 정보를 아이템 ID 를 Key 로 하는 TMap 에 넣는다.
	for (int32 i = 0; i < arrTableData.Num(); ++i)
	{
		m_mapItemInfo.Add(arrTableData[i]->ID, *arrTableData[i]);
	}
}

void UInventoryManager::AddGameItem(EITEM_ID _ID)
{
	// 습득한 아이템 아이디에 해당하는 아이템 정보를 가져온다.
	FGameItemInfo* pItemInfo = m_mapItemInfo.Find(_ID);

	if (nullptr == pItemInfo)
	{
		LOG(LogTemp, Error, TEXT("ITME ID 에 해당하는 아이템 정보 찾을 수 없음"));
		return;
	}


	// 아이템 타입에 맞는 백팩에 접근 후, 해당 아이템을 이미 보유하고있는지 확인
	FItemStack* pItemStack = m_BackPack[(int32)pItemInfo->TYPE].Find(_ID);

	if (nullptr == pItemStack)
	{
		m_BackPack[(int32)pItemInfo->TYPE].Add(_ID, FItemStack{ pItemInfo , 1 });
	}
	else
	{
		++pItemStack->Stack;
	}

	// 현재 게임모드를 체크
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
	{
		return;
	}

	// 게임모드로 부터 메인 HUD 가져오기
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	// 인벤토리 UI 가 열려있으면 내용을 다시 갱신
	if (MainHUD->IsInventoryOpen())
	{
		ResetWidget();
	}
}

void UInventoryManager::OpenInventoryUI()
{
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
	{
		return;
	}

	// 게임모드로 부터 메인 HUD 가져오기
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	ResetWidget();

	// InventoryWidget Visible
	MainHUD->ShowInventoryUI(true);

	// 플레이어 컨트롤러의 입력모드를 UI 모드로 전환한다.
	APlayerController* pController = m_World->GetFirstPlayerController();

	FInputModeUIOnly uionly{};
	pController->SetInputMode(uionly);
	pController->bShowMouseCursor = true;
}

void UInventoryManager::CloseInventoryUI()
{
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
		return;

	// 게임모드로 부터 메인 HUD 가져오기
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	// 인벤토리 위젯 시각화 끄기
	MainHUD->ShowInventoryUI(false);

	// 플레이어 컨트롤러의 입력모드를 Game 모드로 전환한다.
	APlayerController* pController = m_World->GetFirstPlayerController();

	FInputModeGameOnly gonly{};
	pController->SetInputMode(gonly);
	pController->bShowMouseCursor = false;


}

void UInventoryManager::ResetWidget()
{
	APracticeGameModeBase* GameMode = Cast<APracticeGameModeBase>(UGameplayStatics::GetGameMode(m_World));
	if (!IsValid(GameMode))
		return;

	// 게임모드로 부터 메인 HUD 가져오기
	UMainHUDWidget* MainHUD = GameMode->GetMainHUD();

	// MainHUD 로부터 InventoryWidget(UI) 가져오기
	UInventory_Base* InventoryWidget = MainHUD->GetInventoryWidget();

	// InventoryWidget(UI) 이전 내용 클리어하기
	InventoryWidget->Clear();

	for (int32 i = 0; i < (int32)EITEM_TYPE::END; ++i)
	{
		for (auto Iterator = m_BackPack[i].CreateConstIterator(); Iterator; ++Iterator)
		{
			UInvenItemData* pData = NewObject<UInvenItemData>();

			pData->SetIconImgPath(Iterator.Value().ItemInfo->IconPath);
			pData->SetItemName(Iterator.Value().ItemInfo->Description);
			pData->SetItemDescription(Iterator.Value().ItemInfo->Description);
			pData->SetItemCount(Iterator.Value().Stack);

			InventoryWidget->AddItem(pData);
		}
	}
}
