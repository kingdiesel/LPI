#include "ListInventoryAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <cassert>

ListInventoryAction::ListInventoryAction()
{
	AddVerb("INVENTORY");
}

void ListInventoryAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	return Execute(nullptr, results);
}

void ListInventoryAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	results.m_success = true;
	const std::vector<SceneObject*>& SceneObjects = SceneManager::GetInstance()->GetCharacterScene()->GetSceneObjects();
	if (SceneObjects.size() != 0)
	{
		results.m_result_string = "Your inventory contains:\n";
		for (const SceneObject* SceneObject : SceneObjects)
		{
			results.m_result_string += "-";
			results.m_result_string += SceneObject->GetShortName();
			results.m_result_string += "\n";
		}
	}
	else
	{
		results.m_result_string = ListInventoryAction::GetEmptyInventoryString();
	}
}

bool ListInventoryAction::IsValidPayload(SceneObject* payload)
{
	return payload == nullptr;
}

bool ListInventoryAction::IsValidPayload(std::vector<SceneObject*> payload)
{
	return payload.size() == 0;
}

std::string ListInventoryAction::GetEmptyInventoryString()
{
	return "There is nothing in your inventory.\n";
}

void ListInventoryAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot see your inventory right now.\n";
}
