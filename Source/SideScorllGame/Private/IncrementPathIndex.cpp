// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementPathIndex.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AISideCharacter.h"
#include "Blackboard_Keys.h"
#include <cmath>

UIncrementPathIndex::UIncrementPathIndex(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Increment Path Index");
}


EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get the Ai controller
	AEnemy_AIController* const controller = Cast< AEnemy_AIController>(owner_comp.GetAIOwner());
	AAISideCharacter* const npc = Cast< AAISideCharacter>(controller->GetPawn());
	int const no_of_points = npc->num();
	int const min_idex = 0;
	int const max_index = no_of_points - 1;

	//get and set the black board index key
	int index = controller->get_blackboard()->GetValueAsInt(bb_keys::patrol_path_index);
	if (bidirectional)
	{
		if (index >= max_index && direction == EDirectionType::Forward)
		{
			direction = EDirectionType::Reverse;
		}
		else if (index == min_idex && direction == EDirectionType::Reverse)
		{
			direction = EDirectionType::Forward;
		}
	}
	controller->get_blackboard()->SetValueAsInt(bb_keys::patrol_path_index,
		(direction == EDirectionType::Forward ? std::abs(++index) : std::abs(--index)) % no_of_points);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(max_index));
	//Finsh with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
