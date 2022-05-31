// Fill out your copyright notice in the Description page of Project Settings.


#include "SideCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"

ASideCharacter::ASideCharacter()
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

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));

}


//--------------------------------------------Functions-------------------------------------------------------//

void ASideCharacter::Updata_FlipSprite()
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

void ASideCharacter::SpriteToCamera()
{
	GetSprite()->SetWorldRotation(FRotator(0.f, FindLookatCameraZ() - 90.f, 0.f));
}

float ASideCharacter::FindLookatCameraZ()
{
	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	return PlayerRot.Yaw;
}

//--------------------------------------------Basic handle-------------------------------------------------------//

void ASideCharacter::MoveRight(float Value)
{
	if ((Controller != NULL))
	{
		// get right vector // add movement in that direction
		const FVector Direction = FVector(1.f, 0.f, 0.f);

		AddMovementInput(Direction, Value);

		DirectionRight = Value;

		//MakeNoise(1, this, GetActorLocation());

		Updata_Animation();

		Updata_FlipSprite();
	}
}

void ASideCharacter::MoveUp(float Value)
{
	if ((Controller != NULL))
	{
		// get right vector // add movement in that direction
		const FVector Direction = FVector(0.f, 1.f, 0.f);

		AddMovementInput(Direction, Value);

		DirectionUp = Value;

		Updata_Animation();

		//Updata_FlipSprite();
	}
}

/*
void ASideCharacter::Dash()
{
	if (DirectionUp != 0.f || DirectionRight != 0.f)
	{
		FVector DashValue = FVector(DirectionRight, DirectionUp, 0.f) * 1000;

		bDash = true;

		LaunchCharacter(DashValue, false, false);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Action"));

	}
}
*/



void ASideCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASideCharacter::Dash);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &ASideCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASideCharacter::MoveUp);
}

void ASideCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Call your functions

	//SpriteToCamera();
}