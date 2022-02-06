#include "PickupAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <cassert>
#include <Objects/SceneInventoryObject.h>

PickupAction::PickupAction()
{
	AddVerb("TAKE");
	AddVerb("GET");
	AddVerb("PICKUP");
	// TODO: support "pick up"
}

void PickupAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	assert(false);
}

void PickupAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	assert(payload != nullptr);
	Scene* parent_scene = payload->GetParentScene();
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
	results.m_result_string += ".";
}

bool PickupAction::IsValidPayload(SceneObject* payload)
{
	if (SceneInventoryObject* inventory_object = dynamic_cast<SceneInventoryObject*>(payload))
	{
		return true;
	}
	return false;
}

bool PickupAction::IsValidPayload(std::vector<SceneObject*> payload)
{
	if (payload.size() == 1)
	{
		return IsValidPayload(payload[0]);
	}
	return false;
}
