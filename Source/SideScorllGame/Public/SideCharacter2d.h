// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SideCharacter2d.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCORLLGAME_API ASideCharacter2d : public APaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

public:
	ASideCharacter2d(); //Initialize

public:
	UFUNCTION(BlueprintCallable)
	void Updata_FlipSprite();

//--------------------------------------------Basic handle-------------------------------------------------------//
protected:
	void MoveRight(float Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
