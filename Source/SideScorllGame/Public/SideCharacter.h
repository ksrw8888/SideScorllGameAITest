// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SideCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCORLLGAME_API ASideCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnNoiseEmitterComponent* NoiseEmitter;

	public:
		ASideCharacter(); //Initialize


		//--------------------------------------------Functions-------------------------------------------------------//
	public:
		UFUNCTION(BlueprintCallable)
		void Updata_FlipSprite();

		UFUNCTION(BlueprintImplementableEvent)
		void Updata_Animation();


	protected:

		UFUNCTION(BlueprintCallable)
		void SpriteToCamera();

		UFUNCTION(BlueprintCallable)
		float FindLookatCameraZ();

	//--------------------------------------------Basic handle-------------------------------------------------------//
	protected:
		void MoveRight(float Value);

		void MoveUp(float Value);

		UFUNCTION(BlueprintImplementableEvent)
		void Dash();

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		int32 AnimSet = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		int32 WalkSet = 0;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Direction )
		float DirectionRight = 0.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Direction)
		float DirectionUp = 0.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool bDeath = NULL;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool bDash = NULL;
	public:
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		virtual void Tick(float DeltaSeconds) override;
};
