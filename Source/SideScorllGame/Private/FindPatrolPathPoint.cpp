// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPathPoint.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AISideCharacter.h"
#include "Blackboard_Keys.h"

UFindPatrolPathPoint::UFindPatrolPathPoint(FObjectInitializer const& object_initializer)
{
    NodeName = TEXT("Find Patrol Path Point");
}

EBTNodeResult::Type UFindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    //get the AI controller for the patrolling NPC
    AEnemy_AIController* const controller = Cast< AEnemy_AIController>(owner_comp.GetAIOwner());

    //get the current patrol path index from the blackboard
    int const index = controller->get_blackboard()->GetValueAsInt(bb_keys::patrol_path_index);

    //use the index to get the current patrol path
    AAISideCharacter* const npc = Cast< AAISideCharacter>(controller->GetPawn());
    FVector const point = npc->get_patrol_point(index);

    //transform this point to a gloal position using its parent
   // FVector const global_point = npc->GetActorTransform().TransformPosition(point);

    //write the current global path point to the blackboard
    controller->get_blackboard()->SetValueAsVector(bb_keys::patrol_path_vector, point);

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(index));
    //Finsh with success
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

//°Ñ¦Òhttps://www.youtube.com/watch?v=99NT6lQ6SJ0&t=301s