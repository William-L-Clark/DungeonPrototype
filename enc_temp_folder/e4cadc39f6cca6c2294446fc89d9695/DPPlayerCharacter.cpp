// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPPlayerCharacter.h"

// Sets default values
ADPPlayerCharacter::ADPPlayerCharacter()
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ADPPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADPPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &ADPPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ADPPlayerCharacter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADPPlayerCharacter::Jump);

}

void ADPPlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0.f, Rotation.Yaw, 0.f);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, Value);
	}
}

void ADPPlayerCharacter::MoveRight(float Value)
{
	if (Controller && Value)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0.f, Rotation.Yaw, 0.f);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, Value);
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
		AddControllerYawInput(Value);
	}
}

