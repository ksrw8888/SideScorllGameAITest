// Fill out your copyright notice in the Description page of Project Settings.


#include "SideCharacter2dIn3d.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//Initialize
ASideCharacter2dIn3d::ASideCharacter2dIn3d()
{
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	//Create a camera boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	//Create a camera
	Camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	//Set CharacterMovement
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

//--------------------------------------------Functions-------------------------------------------------------//

void ASideCharacter2dIn3d::SpriteToCamera()
{
	GetSprite()->SetWorldRotation(FRotator(0.f, FindLookatCameraZ() - 90.f, 0.f ));
}

float ASideCharacter2dIn3d::FindLookatCameraZ()
{
	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	return PlayerRot.Yaw;
}

//--------------------------------------------Basic handle-------------------------------------------------------//

void ASideCharacter2dIn3d::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector // add movement in that direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}

}

void ASideCharacter2dIn3d::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector // add movement in that direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, Value);

	}
}

void ASideCharacter2dIn3d::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASideCharacter2dIn3d::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASideCharacter2dIn3d::Turn(float Rate)
{
	Super::AddControllerYawInput(Rate);
}

void ASideCharacter2dIn3d::LookUp(float Rate)
{
	Super::AddControllerPitchInput(Rate);
}

void ASideCharacter2dIn3d::Dash()
{
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void ASideCharacter2dIn3d::StopDash()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ASideCharacter2dIn3d::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASideCharacter2dIn3d::Dash);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &ASideCharacter2dIn3d::StopDash);


	PlayerInputComponent->BindAxis("MoveUp", this, &ASideCharacter2dIn3d::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASideCharacter2dIn3d::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &ASideCharacter2dIn3d::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASideCharacter2dIn3d::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ASideCharacter2dIn3d::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASideCharacter2dIn3d::LookUpAtRate);
}

void ASideCharacter2dIn3d::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Call your functions
	
	SpriteToCamera();
}