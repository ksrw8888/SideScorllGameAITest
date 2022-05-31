// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Engine/EngineTypes.h"
#include "Blackboard_Keys.h"
#include "SideCharacter.h"


AEnemy_AIController::AEnemy_AIController(FObjectInitializer const& object_initializer)
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI_System/AI_BT.AI_BT'"));
    if (obj.Succeeded())
    {
        btree = obj.Object;
    }

    behavior_tree_component = object_initializer.CreateAbstractDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

    blackboard = object_initializer.CreateAbstractDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

    setup_perception_system();
}

void AEnemy_AIController::BeginPlay()
{
    Super::BeginPlay();
    RunBehaviorTree(btree);
    behavior_tree_component->StartTree(*btree);
}

void AEnemy_AIController::OnPossess(APawn* const pawn)
{
    Super::OnPossess(pawn);
    if (blackboard)
    {
        blackboard->InitializeBlackboard(*btree->BlackboardAsset);
    }
}

UBlackboardComponent* AEnemy_AIController::get_blackboard() const
{
    return blackboard;
}


void AEnemy_AIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
    if (auto const ch = Cast<ASideCharacter>(actor))
    {
        get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
    }
 
}

void AEnemy_AIController::setup_perception_system()
{
    //create and initialise sight configuration object
    sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    SetPerceptionComponent(*CreateAbstractDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
    sight_config->SightRadius = 500.0f;
    sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
    sight_config->PeripheralVisionAngleDegrees = 90.0f;
    sight_config->SetMaxAge(5.0f);
    sight_config->AutoSuccessRangeFromLastSeenLocation = 900.0f;
    sight_config->DetectionByAffiliation.bDetectEnemies = true;
    sight_config->DetectionByAffiliation.bDetectFriendlies = true;
    sight_config->DetectionByAffiliation.bDetectNeutrals = true;

    //add sight configuration component to perception component
    GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
    GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::on_target_detected);
    GetPerceptionComponent()->ConfigureSense(*sight_config);
}


