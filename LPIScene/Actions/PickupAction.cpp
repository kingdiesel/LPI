#include "PickupAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Components/InventoryItemComponent.h"
#include "Scene/Scene.h"
#include <cassert>

PickupAction::PickupAction()
{
	AddVerb("TAKE");
	AddVerb("GET");
	AddVerb("PICKUP");
	// TODO: support "pick up"
}

void PickupAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	if (payload.size() == 1)
	{
		Execute(payload[0], results);
	}
	else
	{
		assert(false);
	}
}

void PickupAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	assert(payload != nullptr);
	Scene* parent_scene = payload->GetParentScene();
	if (parent_scene == SceneManager::GetInstance()->GetCharacterScene())
	{
		results.m_success = false;
		results.m_show_result_on_failure = true;
		results.m_result_string = "You're already holding that.\n";
	}
	else
	{
		if (parent_scene != nullptr)
		{
			parent_scene->RemoveSceneObject(payload->GetID());
		}
		SceneManager::GetInstance()->GetCharacterScene()->AddSceneObject(payload);
		SceneManager::GetInstance()->m_scene_change_cb.operator()(
			payload,
			parent_scene,
			SceneManager::GetInstance()->GetCharacterScene()
			);
		results.m_success = true;
		results.m_result_string += "You picked up ";
		results.m_result_string += payload->GetShortName();
		results.m_result_string += ".\n";
	}
}

bool PickupAction::IsValidPayload(const SceneObject* payload) const
{
	return payload != nullptr && payload->GetIsValid() &&
		payload->GetInventoryItemComponent() != nullptr;
}

bool PickupAction::IsValidPayload(const std::vector<SceneObject*> payload) const
{
	if (payload.size() == 1)
	{
		return IsValidPayload(payload[0]);
	}
	return false;
}

void PickupAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot pick that up.\n";
}
