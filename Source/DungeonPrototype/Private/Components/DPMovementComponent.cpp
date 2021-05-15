// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DPMovementComponent.h"
#include "Player/DPPlayerCharacter.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Setup Default
UDPMovementComponent::UDPMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Sprint Defaults
	WalkSpeed = 600.f;
	MaxWalkSpeed = WalkSpeed;
	SprintSpeed = 1800.f;

	//Dash Defaults
	DashDistance = 3000.f;
	DashCooldown = 3.f;
	DashStop = 0.2;
	MaxDashStack = 2;
	DashStack = MaxDashStack;
	bHasTouchedGround = true;

	//Multi Jump Defaults
	MaxJumps = 2;
	JumpCount = 0;
}

bool UDPMovementComponent::bCanDash()
{
	return (DashStack > 0 && DashStack <= MaxDashStack && Velocity.Size() > 0.f);
}

void UDPMovementComponent::Dash()
{
	MoveDirection = GetPawnOwner()->GetLastMovementInputVector();
	FVector OldLocation = GetPawnOwner()->GetActorLocation();
	if (bCanDash())
	{
		MoveDirection.Normalize();
		/* Use if Teleport Method
		FVector DashLocation = OldLocation + (MoveDirection * DashDistance);*/
		FVector DashVelocity = FVector(MoveDirection.X, MoveDirection.Y, 0.f).GetSafeNormal() * DashDistance;
		if (!IsMovingOnGround())
		{
			bHasTouchedGround = false;
		}
		BrakingFrictionFactor = 0.f;
		Launch(DashVelocity);
		/* Alternative Dash is teleport player
		GetPawnOwner()->SetActorLocation(DashLocation, false, nullptr, ETeleportType::TeleportPhysics); */
		DashStack--;
		GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &UDPMovementComponent::StopDash, DashStop, false);
	}
}

void UDPMovementComponent::StopDash()
{
	StopMovementImmediately();
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &UDPMovementComponent::DashReset, DashCooldown, false);
	BrakingFrictionFactor = 2.f;
}

void UDPMovementComponent::DashReset()
{
	if (bHasTouchedGround && DashStack < MaxDashStack)
	{
		DashStack = MaxDashStack;
	}
}

void UDPMovementComponent::Sprint()
{
	MaxWalkSpeed = SprintSpeed;
}

void UDPMovementComponent::Walk()
{
	MaxWalkSpeed = WalkSpeed;
}

void UDPMovementComponent::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	Super::ProcessLanded(Hit, remainingTime, Iterations);
	JumpCount = 0;
	bHasTouchedGround = true;
}

bool UDPMovementComponent::DoJump(bool bReplayingMoves)
{
	if (Super::DoJump(bReplayingMoves))
	{
		JumpCount++;
		return true;
	}

	return false;
}

bool UDPMovementComponent::bCanJump()
{
	return (IsMovingOnGround() || JumpCount < MaxJumps) && CanEverJump();
}
