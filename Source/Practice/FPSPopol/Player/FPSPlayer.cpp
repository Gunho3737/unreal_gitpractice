// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayer.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "../../GameInstance_Base.h"
#include "../FPSPlayLevelGamemode.h"

#include "../../Effect/EffectManager.h"
#include "../../Effect/Effect_Base.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
	: ShootAnimationPlay(false), ReloadAnimationPlay(false), bullet(50), MaxHP(100.0f), CurHP(100.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//카메라 컴포넌트를 캡슐에 부착
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	m_Arm->SetupAttachment(GetCapsuleComponent());
	//카메라는 카메라암에 부착
	m_Cam->SetupAttachment(m_Arm);

	ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Script/Engine.AnimBlueprint'/Game/FPSPopol/Character/Animation/Anim_FPSPlayer.Anim_FPSPlayer_C'"));

	if (anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(anim.Class);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("/Script/Engine.AnimMontage'/Game/FPSPopol/Character/Animation/AMT_FPSPlayerAttack.AMT_FPSPlayerAttack'"));

	if (Montage.Succeeded())
	{
		AttackMontage = Montage.Object;
	}


	ConstructorHelpers::FClassFinder<ABullet> Bullet(TEXT("/Script/Engine.Blueprint'/Game/FPSPopol/Bullet/BPC_Bullet.BPC_Bullet_C'"));

	if (Bullet.Succeeded())
	{
		m_Bullet = Bullet.Class;
	}

}

AFPSPlayer::~AFPSPlayer()
{
}

void AFPSPlayer::Move(const FInputActionInstance& _Instance)
{
	//인풋값을 벡터2d로 받아옴
	FVector2D vInput = _Instance.GetValue().Get<FVector2D>();


	if (vInput.X == 1.f)
	{
		GetCharacterMovement()->AddInputVector(GetActorForwardVector() * vInput.X);
	}
	else if (vInput.X == -1.f)
	{
		GetCharacterMovement()->AddInputVector(GetActorForwardVector() * vInput.X);
		vInput.X = 0.f;
	}

	if (vInput.Y != 0.f)
		GetCharacterMovement()->AddInputVector(GetActorRightVector() * vInput.Y);
}

void AFPSPlayer::Rotation(const FInputActionInstance& _Instance)
{
	//rotate 구조를 공부할것
	//카메라 암을 돌리는거로 카메라를 회전

	FVector2D vInput = _Instance.GetValue().Get<FVector2D>();

	// Pitch, Yaw, Roll
	AddControllerYawInput(vInput.X);

	float DT = GetWorld()->GetDeltaSeconds();

	FRotator rot = m_Arm->GetRelativeRotation();
	rot.Pitch += vInput.Y * 100.f * DT;

	if (rot.Pitch > 40)
		rot.Pitch = 40.f;
	else if (rot.Pitch < -40.f)
		rot.Pitch = -40.f;

	m_Arm->SetRelativeRotation(rot);
}

void AFPSPlayer::Jump(const FInputActionInstance& _Instance)
{
	Super::Jump();
}

void AFPSPlayer::Attack(const FInputActionInstance& _Instance)
{
	bool bToggle = _Instance.GetValue().Get<bool>();

	if (!IsValid(GetMesh()->GetAnimInstance()) || AttackMontage.IsNull())
	{
		//애님 인스턴스가 없거나 공격 몽타쥬 세팅이 안되어있으면 리턴
		return;
	}

	if (ReloadAnimationPlay == true)
	{
		//현재 재장전 애니메이션 실행중이면 리턴한다
		//컨트롤하는건 애님 인스턴스
		return;
	}


	if (ShootAnimationPlay == true)
	{
		//현재 발사 애니메이션 실행중이면 리턴한다
		//컨트롤하는건 애님 인스턴스
		return;
	}

	//총알이 0보다 작을경우
	if (bullet <= 0)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage.LoadSynchronous());
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(TEXT("Reload"), AttackMontage.LoadSynchronous());
		return;
	}

	if (bToggle == true)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage.LoadSynchronous());
		bullet -= 1;

		////스폰 액터를 위해 필요한 세팅이 담긴 클래스 param
		FActorSpawnParameters param = {};
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //스폰세팅, 충돌체와 상관없이 지정해준 위치에서 항상 생성
		param.OverrideLevel = GetLevel();
		param.bDeferConstruction = false;	// 지연생성(BeginPlay 바로호출 X)
		
		// 카메라 위치 + 카메라 전방방향 * 10미터
		FVector CamForwardPos = m_Cam->GetComponentLocation() + m_Cam->GetForwardVector() * 1000;
		
		// 투사체 생성위치, 소켓을 넣어줌
		FVector ProjectileLocation = GetMesh()->GetSocketLocation(FName(TEXT("Muzzle_01")));

		// 투사체 위치에서 카메라 전방 10미터 위치를 향하는 방향벡터 구하기
		FVector vDir = CamForwardPos - ProjectileLocation;
		vDir.Normalize();

		//투사체의 속도는 전방벡터 5000.f
		AProjectile* pProjectile = GetWorld()->SpawnActor<AProjectile>(m_Bullet, ProjectileLocation, FRotator(), param);
		pProjectile->m_ProjtileMovement->Velocity = vDir * 10000.f;
	}
}

void AFPSPlayer::BulletReload()
{
	//총알 갯수 리로드하기
	bullet = 50;
}

void AFPSPlayer::HPChange(float _DMG)
{
	CurHP += _DMG;

	if (CurHP > MaxHP)
	{
		CurHP = MaxHP;
	}

	float HPRatio = CurHP / MaxHP;

	CharHud->SetPlayerHPRatio(HPRatio);
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pController = Cast<APlayerController>(GetController());

	if (pController)
	{
		ULocalPlayer* pLocalPlayer = pController->GetLocalPlayer();

		if (pLocalPlayer && !InputMapping.IsNull())
		{
			UEnhancedInputLocalPlayerSubsystem* pSubsystem = pLocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			pSubsystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
		}
	}
	
	//게임모드 받아와서 FPSGameMode로 다운캐스팅
	AFPSPlayLevelGamemode* FGM = Cast<AFPSPlayLevelGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(FGM))
	{
		CharHud = FGM->GetMainHUD();
	}

	//플레이어 HPBar테스트
	//CharHud->SetPlayerHPRatio(0.5f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	CharHud->SetPlayerHPRatio(1.0f);
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* InputCom = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (nullptr == InputCom)
		return;

	if (!MoveAction.IsNull())
	{
		InputCom->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AFPSPlayer::Move);
	}

	if (!RotationAction.IsNull())
	{
		InputCom->BindAction(RotationAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AFPSPlayer::Rotation);
	}

	if (!JumpAction.IsNull())
	{
		InputCom->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AFPSPlayer::Jump);
	}

	if (!AttackAction.IsNull())
	{
		InputCom->BindAction(AttackAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &AFPSPlayer::Attack);
	}
}

