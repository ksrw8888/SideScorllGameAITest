// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AISideCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCORLLGAME_API AAISideCharacter : public APaperCharacter
{
	GENERATED_BODY()

	// 定義PawnSensing組件
	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//class UPawnSensingComponent* PawnSensingComp;

	public:
		AAISideCharacter(); //Initialize

	protected:

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
	/*	// 定義SeePawn的回調
		UFUNCTION()
		void OnMySeePawn(APawn* Pawn);

		// 定義HearPawn的回調
		UFUNCTION()
		void OnHeardNoise(APawn* NoiseInstigator, const FVector& Location, float Volume);
	*/
		UFUNCTION(BlueprintCallable)
		void Updata_FlipSprite();

		UFUNCTION(BlueprintImplementableEvent)
		void Updata_Animation();

		virtual void Tick(float DeltaSeconds) override;

		FVector get_patrol_point(int const index) const;

		int num() const;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		int32 AnimSet = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		int32 WalkSet = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool bDeath = NULL;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool bDash = NULL;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PatrolPath", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"));
		TArray<FVector> patrol_points;

	private:		
		class UAIPerceptionStimuliSourceComponent* stimulus;

		void setup_stimulus();
		
};
