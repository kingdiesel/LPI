#include "UseAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Components/UseComponent.h"
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
	results.m_success = true;
	if (payload != nullptr)
	{
		results.m_result_string = payload->GetDescription();
	}
	else
	{
		results.m_result_string = SceneManager::GetInstance()->GetCurrentScene()->GetSceneDescription();
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
