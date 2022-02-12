#include "LookAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <cassert>

LookAction::LookAction()
{
	AddVerb("LOOK");
}

void LookAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	results.m_success = false;
	if (payload.size() == 1)
	{
		return Execute(payload[0], results);
	}
	
	return Execute(nullptr, results);
}

void LookAction::Execute(SceneObject* payload, ExecuteResults& results)
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

bool LookAction::IsValidPayload(SceneObject* payload)
{
	return true;
}

bool LookAction::IsValidPayload(std::vector<SceneObject*> payload)
{
	return payload.size() == 1 || payload.size() == 0;
}

void LookAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot look at that.\n";
}
