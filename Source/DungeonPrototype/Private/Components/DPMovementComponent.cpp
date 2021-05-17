// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DPMovementComponent.h"
#include "Player/DPPlayerCharacter.h"
#include "..\..\Public\Components\DPMovementComponent.h"

UDPMovementComponent::UDPMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//Sprint Defaults
	WalkSpeed = 600.f;
	MaxWalkSpeed = WalkSpeed;
	SprintSpeed = 1800;

	//Dash Defaults
	DashDistance = 3000.f;
	DashCooldown = 3.f;
	DashStop = 0.2f;
	ExtraDashes = 2;
	DashStack = ExtraDashes;
	
	//Multi-jump Defaults
	bHasTouchedGrd = true;
	MaxJumps = 2;
	JumpCount = 0;
	MaxJumpHeight = 600.f;
	JumpZVelocity = MaxJumpHeight;
}

bool UDPMovementComponent::bCanDash()
{
	return (DashStack > 0 && DashStack <= ExtraDashes && Velocity.Size() > 0.0f);
}

void UDPMovementComponent::Dash()
{
	MoveDirection = GetPawnOwner()->GetLastMovementInputVector();
	FVector OldLocation = GetPawnOwner()->GetActorLocation();
	if (bCanDash())
	{
		MoveDirection.Normalize();
		FVector DashVelocity = FVector(MoveDirection.X, MoveDirection.Y, 0.f) * DashDistance;
		if (!IsMovingOnGround())
		{
			bHasTouchedGrd = false;
		}
		BrakingFrictionFactor = 0.f;
		Launch(DashVelocity);
		DashStack--;
		GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &UDPMovementComponent::StopDash, DashStop, false);
	}
	else
	{
		if (!DashCooldownTimerHandle.IsValid() || GetWorld()->GetTimerManager().GetTimerRemaining(DashCooldownTimerHandle) <= 0.f)
		{
			DashReset();
		}
	}
}

void UDPMovementComponent::StopDash()
{
	StopMovementImmediately();
	GetWorld()->GetTimerManager().SetTimer(DashCooldownTimerHandle, this, &UDPMovementComponent::DashReset, DashCooldown, false);
	BrakingFrictionFactor = 2.0f;
}

void UDPMovementComponent::DashReset()
{
	if (bHasTouchedGrd && DashStack < ExtraDashes)
	{
		DashStack = ExtraDashes;
	}
}

bool UDPMovementComponent::CanJump()
{
	return (IsMovingOnGround() || JumpCount < MaxJumps) && CanEverJump();
}

void UDPMovementComponent::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	bHasTouchedGrd = true;
	JumpCount = 0;
	if (GetWorld()->GetTimerManager().GetTimerRemaining(DashCooldownTimerHandle) <= 0.f)
	{
		DashReset();
	}
	Super::ProcessLanded(Hit, remainingTime, Iterations);
}

bool UDPMovementComponent::DoJump(bool bReplayingMoves)
{
	if (Super::DoJump((bReplayingMoves)))
	{
		JumpCount++;
		return true;
	}

	return false;
}

bool UDPMovementComponent::HandlePendingLaunch()
{
	if (!PendingLaunchVelocity.IsZero() && HasValidData()) {
		Velocity = PendingLaunchVelocity;
		PendingLaunchVelocity = FVector::ZeroVector;
		bForceNextFloorCheck = true;
		return true;
	}
	return false;
}
