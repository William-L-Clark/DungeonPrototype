// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DPMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DPPlayerCharacter.generated.h"

UCLASS()
class DUNGEONPROTOTYPE_API ADPPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADPPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		FORCEINLINE class UDPMovementComponent* GetDPMovementComp() const { return DPMovementComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual bool CanJumpInternal_Implementation() const override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	void Dash();
	void Sprint();
	void Walk();

	UPROPERTY(EditAnywhere)
		UCameraComponent* TPCameraComp;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
		UDPMovementComponent* DPMovementComponent;
};
