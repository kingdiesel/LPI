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
	if (payload.size() == 1)
	{
		return Execute(payload[0], results);
	}
	
	return Execute(nullptr, results);
}

void UseAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	if (payload != nullptr)
	{
		results.m_success = true;
		results.m_result_string = SceneManager::GetInstance()->m_scene_object_used_cb.operator()(
			payload,
			nullptr
		);
		
		// if this is a destroy on use item
		if (payload->GetInventoryItemComponent() != nullptr && payload->GetInventoryItemComponent()->GetDestroyOnUse())
		{
			// and it's in the player's inventory
			if (payload->GetParentScene() == SceneManager::GetInstance()->GetCharacterScene())
			{
				// destroy it
				SceneObject* destroyed_object = payload->GetParentScene()->RemoveSceneObject(payload->GetID());
				delete destroyed_object;
			}
		}
	}
}

bool UseAction::IsValidPayload(SceneObject* payload)
{
	return payload->GetUseComponent() != nullptr && payload->GetUseComponent()->GetUsable();
}

bool UseAction::IsValidPayload(std::vector<SceneObject*> payload)
{
	if (!(payload.size() == 1 || payload.size() == 2))
	{
		return false;
	}
	for (SceneObject* object : payload)
	{
		if (!IsValidPayload(object))
		{
			return false;
		}
	}
	return true;
}

void UseAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot use that.\n";
}
