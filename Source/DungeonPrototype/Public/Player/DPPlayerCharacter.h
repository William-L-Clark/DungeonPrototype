// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DPPlayerCharacter.generated.h"

UCLASS()
class DUNGEONPROTOTYPE_API ADPPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADPPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	UPROPERTY(EditAnywhere)
		UCameraComponent* TPCameraComp;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArmComp;
};
