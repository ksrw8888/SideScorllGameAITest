// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SideCharacter2dIn3d.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCORLLGAME_API ASideCharacter2dIn3d : public APaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

public:
	ASideCharacter2dIn3d(); //Initialize

//--------------------------------------------Functions-------------------------------------------------------//
protected:

	UFUNCTION(BlueprintCallable)
	void SpriteToCamera();

	UFUNCTION(BlueprintCallable)
	float FindLookatCameraZ();

//--------------------------------------------Basic handle-------------------------------------------------------//
protected:
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void Turn(float Rate);

	void LookUp(float Rate);

	void Dash();

	void StopDash();
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;
};
