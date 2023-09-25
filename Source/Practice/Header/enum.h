#pragma once

//언리얼 enum을 사용하기 위해 필요한 매크로
//괄호 안에 BlueprintType를 넣어줘서 블루프린트에서도 사용 가능토록함
UENUM(BlueprintType)
enum class EInputActionType : uint8	//Enum명에 E를 붙혀줘서 Enum임을 명확하게함, enum값 하나의 값은 int8
{
	MOVE,
	ROTATION,
	JUMP,
	SPRINT_TOGGLE,
	ATTACK,
	SWORDWAVE,
	RELOAD,
};

UENUM(BlueprintType)
enum class EEFFECT_TYPE : uint8
{
	EXPLODE,
	EMP,
	FIRE,
	ICE,
	SWORDWAVE,
	NONE,
};

//몬스터의 STATE
UENUM(BlueprintType)
enum class EMON_STATE : uint8
{
	IDLE,
	MOVE,
	MELEE_ATTACK,
	RANGE_ATTACK,
	HIT,
	DEAD,
};

//등장하는 몬스터의 종류
UENUM(BlueprintType)
enum class EMON_TYPE : uint8
{
	MELEE,
	RANGE,
	BOSS,
};

//아이템 타입의 ID값
UENUM(BlueprintType)
enum class EITEM_ID : uint8
{
	CI_POTION,
	CI_MEGAPORION,

	EW_LONGSWORD,
	EW_DAGGER,
	EW_BOW,

	EA_LEATHER_ARMOR,
	EA_STEEL_ARMOR,
	EA_PLATINUM_ARMOR
};

//아이템 타입
UENUM(BlueprintType)
enum class EITEM_TYPE : uint8
{
	WEAPON,
	ARMOR,
	ACCESSORY,
	CONSUMABLE,

	END,
};