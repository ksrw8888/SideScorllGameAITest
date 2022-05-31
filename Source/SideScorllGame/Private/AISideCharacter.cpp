// Fill out your copyright notice in the Description page of Project Settings.


#include "AISideCharacter.h"
//#include "Perception/PawnSensingComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blackboard_Keys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Enemy_AIController.h"




// Sets default values
AAISideCharacter::AAISideCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	// 創建組件，注意導入頭文件 Perception/PawnSensingComponent
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAISideCharacter::OnMySeePawn);

	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAISideCharacter::OnHeardNoise);
	PawnSensingComp->LOSHearingThreshold = 1200;

	PawnSensingComp->SetPeripheralVisionAngle(60.0f);

	PawnSensingComp->HearingThreshold = 600;

	PawnSensingComp->SightRadius = 2000;
	*/
	//不讓AI改變rotation
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void AAISideCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i <= num() - 1; i++)
	{
		patrol_points[i] = GetActorTransform().TransformPosition(patrol_points[i]);
	}
		
}
/*
void AAISideCharacter::OnMySeePawn(APawn* Pawn)
{
	//UE_LOG(LogTemp, Warning, TEXT("Has Seen Pawn: "), *(Pawn->GetName()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SeePawn"));

	if (auto const AIController = Cast<AEnemy_AIController>(GetController()))
	{
		AIController->get_blackboard()->SetValueAsBool(bb_keys::can_see_player, true);
	}

}

void AAISideCharacter::OnHeardNoise(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hear %s fired noise at location: %s"), *(NoiseInstigator->GetName()), *(Location.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HearNoise"));

	if (auto const AIController = Cast<AEnemy_AIController>(GetController()))
	{
		AIController->get_blackboard()->SetValueAsBool(bb_keys::can_see_player, true);
	}

}
*/

void AAISideCharacter::Updata_FlipSprite()
{
	const float VelocityX = GetMovementComponent()->Velocity.X;
	const float VelocityY = GetMovementComponent()->Velocity.Y;

	//因bUseControllerRotationYaw = false所以改成只翻轉圖片
	if (VelocityX < 0.f)
	{
		GetController()->SetControlRotation(FRotator(0.f, 180.f, 0.f));
		GetSprite()->SetWorldRotation(FRotator(0.f, 180.f, 0.f));	
	}
	else if (VelocityX > 0.f)
	{
		GetController()->SetControlRotation(FRotator(0.f, 0.f, 0.f));
		GetSprite()->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
	}
	else
	{
		if (VelocityY < 0.f)
		{
			GetSprite()->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
			GetController()->SetControlRotation(FRotator(0.f, 90.f, 0.f));
		}
		else if (VelocityY > 0.f)
		{
			GetSprite()->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
			GetController()->SetControlRotation(FRotator(0.f, 270.f, 0.f));
		}
	}

}

void AAISideCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Call your functions

	Updata_Animation();
	Updata_FlipSprite();
	
	
}

FVector AAISideCharacter::get_patrol_point(int const index) const
{
	return patrol_points[index];
}

int AAISideCharacter::num() const
{
	return patrol_points.Num();
}


void AAISideCharacter::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}
