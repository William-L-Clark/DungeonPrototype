// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DPMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROTOTYPE_API UDPMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

public: 

	/// Dash

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashStop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		int ExtraDashes;
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Dash")
		int DashStack;
	UPROPERTY()
		FVector MoveDirection;
	UPROPERTY()
		FTimerHandle DashTimerHandle;
	UPROPERTY()
		FTimerHandle DashCooldownTimerHandle;
	
	UFUNCTION()
		bool bCanDash();
	UFUNCTION(BlueprintCallable, Category = "Dash")
		void Dash();
	UFUNCTION(BlueprintCallable, Category = "Dash")
		void StopDash();
	UFUNCTION(BlueprintCallable, Category = "Dash")
		void DashReset();

	//Sprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
		float SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
		float WalkSpeed;

	// Multi-Jump
	UPROPERTY()
		bool bHasTouchedGrd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-Jump")
		int MaxJumps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-Jump")
		int JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multi-Jump")
		float MaxJumpHeight;
	UFUNCTION()
		bool CanJump();

	virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;
	virtual bool DoJump(bool bReplayingMoves) override;
	virtual bool HandlePendingLaunch() override;

};
