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


	///==========================
	///		DASH
	///==========================
	
	UPROPERTY(EditAnywhere, Category = "Dash")
		float DashDistance;
	UPROPERTY(EditAnywhere, Category = "Dash")
		float DashCooldown;
	UPROPERTY(EditAnywhere, Category = "Dash")
		float DashStop;
	UPROPERTY(EditAnywhere, Category = "Dash")
		float DashGRDMultiplyer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		int MaxDashStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		int DashStack;
	UPROPERTY()
		bool bHasTouchedGround;

	UFUNCTION()
		bool bCanDash();
	UFUNCTION()
		void Dash();
	UFUNCTION()
		void StopDash();
	UFUNCTION()
		void DashReset();

	FVector MoveDirection;

///=========================================
///					Sprint
///=========================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
		float SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
		float WalkSpeed;
	UFUNCTION()
		void Sprint();
	UFUNCTION()
		void Walk();
///==========================================
///				Double Jump
///==========================================
	virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;
	virtual bool DoJump(bool bReplayingMoves) override;
	bool bCanJump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MultiJump")
		int MaxJumps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MultiJump")
		int JumpCount;
	UPROPERTY()
		FTimerHandle DashTimerHandle;

};
