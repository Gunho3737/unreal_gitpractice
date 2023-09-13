// Fill out your copyright notice in the Description page of Project Settings.
#include "Character_Base.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Effect/EffectManager.h"
#include "../Effect/Effect_Base.h"


// Sets default values
ACharacter_Base::ACharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera Component �� SpringArm Component �� �����ؼ� ACharacter_Base Actor ���� �߰�
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	// SceneComponent ������ �������� ���� ����	
	m_Arm->SetupAttachment(GetCapsuleComponent());
	m_Cam->SetupAttachment(m_Arm);

	//AnimInstance�� ������
	ConstructorHelpers::FClassFinder<UAnimInstance> anim(TEXT("/Script/Engine.AnimBlueprint'/Game/MyCharacter/Character/Animation/ABP_Grey.ABP_Grey'"));

	if (anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(anim.Class);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Montage(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacter/Character/Animation/AM_Grey.AM_Grey'"));

	if (Montage.Succeeded())
	{
		AttackMontage = Montage.Object;
	}
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
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
	
	//캡슐컨퍼넌트에 충돌함수 바인딩
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ACharacter_Base::OnHit);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Base::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACharacter_Base::EndOverlap);

}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* InputCom = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//���� ����� ������ �ʾҴٸ� �״�� ����
	if (nullptr == InputCom)
		return;

	//��ǲ �׼��� ���ε�
	if (!MoveAction.IsNull())
	{
		//InputCom->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Move);
	}

	if (!RotationAction.IsNull())
	{
		//InputCom->BindAction(RotationAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Rotation);
	}

	if (!SprintToggleAction.IsNull())
	{
		//InputCom->BindAction(SprintToggleAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::SprintToggle);
	}

	if (!JumpAction.IsNull())
	{
		//InputCom->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Jump);
	}

	//데이터에셋을 받아와 액션인풋 바인딩을 해준다
	if (!InputActionSetting.IsNull())
	{
		UIA_DataAsset* pDA = InputActionSetting.LoadSynchronous();

		for (int32 i = 0; i < pDA->IADataArr.Num(); ++i)
		{
			if (pDA->IADataArr[i].Action.IsNull())
				continue;

			switch (pDA->IADataArr[i].Type)
			{
			case EInputActionType::MOVE:
				InputCom->BindAction(pDA->IADataArr[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Move);
				break;
			case EInputActionType::ROTATION:
				InputCom->BindAction(pDA->IADataArr[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Rotation);
				break;
			case EInputActionType::JUMP:
				InputCom->BindAction(pDA->IADataArr[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Jump);
				break;
			case EInputActionType::SPRINT_TOGGLE:
				InputCom->BindAction(pDA->IADataArr[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::SprintToggle);
				break;
			case EInputActionType::ATTACK:
				InputCom->BindAction(pDA->IADataArr[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::Attack);
				break;
			case EInputActionType::SWORDWAVE:
				InputCom->BindAction(pDA->IADataArr[i].Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &ACharacter_Base::SwordWave);
				break;
			case EInputActionType::RELOAD:
				break;
			}
		}
	}

}

void ACharacter_Base::Move(const FInputActionInstance& _Instance)
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

	//y�� ������� �������� ������ ���Ϳ� ���� �¿��̵� ����
	if (vInput.Y != 0.f)
		GetCharacterMovement()->AddInputVector(GetActorRightVector() * vInput.Y);
}

void ACharacter_Base::Rotation(const FInputActionInstance& _Instance)
{
	//rotate 구조를 공부할것

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

void ACharacter_Base::SprintToggle(const FInputActionInstance& _Instance)
{
	//현재 토글 여부를 체크
	bool bToggle = _Instance.GetValue().Get<bool>();

	if (bToggle)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
}

void ACharacter_Base::Jump(const FInputActionInstance& _Instance)
{
	Super::Jump();
}

void ACharacter_Base::Attack(const FInputActionInstance& _Instance)
{
	//UE_LOG(LogTemp, Warning, TEXT("!!!Call Attack Function!!!"));

	bool bToggle = _Instance.GetValue().Get<bool>();

	if (!IsValid(GetMesh()->GetAnimInstance()) || AttackMontage.IsNull())
	{
		//애님 인스턴스가 없거나 공격 몽타쥬 세팅이 안되어있으면 리턴
		return;
	}

	if (bToggle == true)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage.LoadSynchronous());
	//	GetMesh()->GetAnimInstance()->Montage_JumpToSection(TEXT("Combo"), AttackMontage.LoadSynchronous());
		IsAttack = true;
	}
	else
	{
		IsAttack = false;
	}

	//플레이어 어택 트레이스 = ECC_GameTraceChannel3;
	ECC_GameTraceChannel3;

	//충돌한 결과값들이 들어갈 TArray
	TArray<FHitResult> ResultArray;
	
	//내가 세팅해준 세팅값이 들어간 객체
	FCollisionQueryParams query(NAME_None, false, this);
	bool bCollision = GetWorld()->SweepMultiByChannel(ResultArray	//결과값이 들어갈 array
		, GetActorLocation(), GetActorLocation()	//충돌체크 시작점과 끝나는 점
		, FQuat::Identity	//기본 사원수값 (1,1,1)
		, ECC_GameTraceChannel3 // PlayerAttack Trace Channel
		, FCollisionShape::MakeSphere(500.f)	//충돌체의 모양, 여기선 구 모양을 만듬
		, query);

	FColor color;
	bCollision ? color = FColor::Red : color = FColor::Green;
	DrawDebugSphere(GetWorld(), GetActorLocation(), 500.f, 40, color, false, 2.f);


	for (int32 i = 0; i < ResultArray.Num(); ++i)
	{
		// 충돌이 일어난 지점에서 Explode Effect 재생해보기
		//UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), ResultArray[i].Location);
	}

}

void ACharacter_Base::SwordWave(const FInputActionInstance& _Instance)
{
	if (IsCombo == false)
	{
		return;
	}
	else
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage.LoadSynchronous());
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(TEXT("Combo"), AttackMontage.LoadSynchronous());
		//실행도중 다시 입력해도 안들어오게 세팅
		IsCombo = false;
	}
}

void ACharacter_Base::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Block Active"));
}

void ACharacter_Base::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OverLap Active"));
	//오버랩 된 다른 오브젝트를 파괴시킨다
	//_OtherActor->Destroy();
}

void ACharacter_Base::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{	
	//explode 이펙트를 플레이어 자리에 발생
//	UEffectManager::GetInst()->CreateEffect(GetWorld(), EEFFECT_TYPE::EXPLODE, GetLevel(), GetActorLocation());
}

