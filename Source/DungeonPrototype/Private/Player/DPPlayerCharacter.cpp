// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPPlayerCharacter.h"

// Sets default values
ADPPlayerCharacter::ADPPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UDPMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	TPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCameraComp"));

	SpringArmComp->SetupAttachment(RootComponent);
	TPCameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 4.f;
	SpringArmComp->bEnableCameraRotationLag = true;
	SpringArmComp->CameraRotationLagSpeed = 8.f;
	SpringArmComp->CameraLagMaxDistance = 1.5f;
	SpringArmComp->CameraLagMaxTimeStep = 1.f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bInheritPitch = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ADPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Component call -> Binding Type -> Input Name -> User Object (this) -> Call Function//
	PlayerInputComponent->BindAxis("MoveForward", this, &ADPPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADPPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &ADPPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ADPPlayerCharacter::Turn);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADPPlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADPPlayerCharacter::Walk);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADPPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ADPPlayerCharacter::Dash);

}


void ADPPlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value)
	{
		const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f); // Gets ControllerRotation and constructs a Yaw Rotator
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X); // Gets Forward Vector
		AddMovementInput(direction, Value); //Calls built in function to move player in firection with the value we provide through input
	}
}

void ADPPlayerCharacter::MoveRight(float Value)
{
	if (Controller && Value)
	{
		const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f); // Gets ControllerRotation and constructs a Yaw Rotator
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y); // Gets Right Vector
		AddMovementInput(direction, Value); //Applies Built in function to move player in Direction with the value we provide through input
	}
}

void ADPPlayerCharacter::LookUp(float Value)
{
	//Advanced Camera Complex
	if (Value)
	{
		float pitch = SpringArmComp->GetRelativeRotation().Pitch + Value;
		if (pitch < 25.f && pitch > -65.f)
		{
			SpringArmComp->AddLocalRotation(FRotator(Value, 0.f, 0.f));
		}
	}

	/*Simple = AddControllerPitchInput()*/
}

void ADPPlayerCharacter::Turn(float Value)
{
	if (Value)
	{
		AddControllerYawInput(Value); //Simplest Already
	}
}

void ADPPlayerCharacter::Dash()
{
	if (DPMovementComponent)
	{
		GetDPMovementComp()->Dash();
	}
}

void ADPPlayerCharacter::Sprint()
{
	if (DPMovementComponent)
	{
		GetDPMovementComp()->Sprint();
	}
}

void ADPPlayerCharacter::Walk()
{
	if (DPMovementComponent)
	{
		GetDPMovementComp()->Walk();
	}
}

void ADPPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DPMovementComponent = Cast<UDPMovementComponent>(Super::GetMovementComponent());
}

bool ADPPlayerCharacter::CanJumpInternal_Implementation() const
{
	bool bCanJump = Super::CanJumpInternal_Implementation();
	if (!bCanJump && GetDPMovementComp())
	{
		bCanJump = GetDPMovementComp()->bCanJump();
	}

	return bCanJump;
}
