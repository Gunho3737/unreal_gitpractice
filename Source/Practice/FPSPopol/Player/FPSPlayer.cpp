// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayer.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "../../GameInstance_Base.h"
#include "../../Effect/EffectManager.h"
#include "../../Effect/Effect_Base.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
	: ShootAnimationPlay(false), ReloadAnimationPlay(false), bullet(100)
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

	if (bToggle == true)
	{
		LOG(LogTemp, Warning, TEXT("AttackFunc Call"));
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage.LoadSynchronous());
		//	GetMesh()->GetAnimInstance()->Montage_JumpToSection(TEXT("Combo"), AttackMontage.LoadSynchronous());
		bullet -= 1;
	}
	
	//총알이 0보다 작을경우
	if (bullet <= 0)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage.LoadSynchronous());
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(TEXT("Reload"), AttackMontage.LoadSynchronous());
	}

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
	
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
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

