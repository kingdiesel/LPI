#include "UseAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Components/UseComponent.h"
#include "Components/InventoryItemComponent.h"
#include <cassert>

UseAction::UseAction()
{
	AddVerb("USE");
}

void UseAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	results.m_success = false;
	if (payload.size() == 1) // unary use
	{
		return Execute(payload[0], results);
	}
	else // binary use
	{
		SceneObject* use_object = payload[0];
		SceneObject* use_target = payload[1];
		results = SceneManager::GetInstance()->m_scene_object_used_cb.operator()(
			use_object,
			use_target
		);

		// if this is a destroy on use item
		if (use_object->GetUseComponent()->GetDestroyOnUse())
		{
			// destroy it
			SceneObject* destroyed_object = use_object->GetParentScene()->RemoveSceneObject(use_object->GetID());
			// TODO: memory leak
			destroyed_object->SetIsValid(false);
		}
	}
	
	return Execute(nullptr, results);
}

void UseAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	if (payload != nullptr)
	{
		results = SceneManager::GetInstance()->m_scene_object_used_cb.operator()(
			payload,
			nullptr
		);
		
		// if this is a destroy on use item
		if (payload->GetUseComponent()->GetDestroyOnUse())
		{
			// destroy it
			SceneObject* destroyed_object = payload->GetParentScene()->RemoveSceneObject(payload->GetID());
			// TODO: memory leak
			destroyed_object->SetIsValid(false);
		}
	}
}

bool UseAction::IsValidPayload(SceneObject* payload)
{
	return payload != nullptr && payload->GetIsValid() && 
		payload->GetUseComponent() != nullptr && payload->GetUseComponent()->GetUsable();
}

bool UseAction::IsValidPayload(std::vector<SceneObject*> payload)
{
	// unary use
	if (payload.size() == 1)
	{
		return IsValidPayload(payload[0]);
	}
	else if (payload.size() == 2)
	{
		const bool valid_use_object = IsValidPayload(payload[0]);
		const bool valid_target = payload[1] != nullptr && payload[1]->GetIsValid();
		return valid_use_object && valid_target;
	}
	return false;
}

void UseAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot use that.\n";
}
