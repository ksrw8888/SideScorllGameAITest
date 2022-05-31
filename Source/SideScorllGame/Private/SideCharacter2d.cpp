// Fill out your copyright notice in the Description page of Project Settings.


#include "SideCharacter2d.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASideCharacter2d::ASideCharacter2d()
{
	//Create a camera boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 75.f);
	SpringArm->bDoCollisionTest = false;
	

	//Create a camera
	SideViewCameraComponent = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("SideViewCameraComponent"));
	SideViewCameraComponent->SetupAttachment(SpringArm);
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.f;

	//Set CharacterMovement
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->BrakingDecelerationFlying = 2048.f;
}

void ASideCharacter2d::Updata_FlipSprite()
{
	const float VelocityX = GetMovementComponent()->Velocity.X;

	if (VelocityX > 0.f)
	{
		GetController()->SetControlRotation(FRotator(0.f, 0.f, 0.f));
	}
	else if (VelocityX < 0.f)
	{
		GetController()->SetControlRotation(FRotator(0.f, 180.f, 0.f));
	}
}

//--------------------------------------------Basic handle-------------------------------------------------------//

void ASideCharacter2d::MoveRight(float Value)
{
	if ((Controller != NULL))
	{
		// get right vector // add movement in that direction
		const FVector Direction = FVector(1.f, 0.f, 0.f);
		AddMovementInput(Direction, Value);

		Updata_FlipSprite();
	}
}


void ASideCharacter2d::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &ASideCharacter2d::MoveRight);
}
