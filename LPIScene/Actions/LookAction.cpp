#include "LookAction.h"
#include "Objects/SceneObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Components/DescriptionComponent.h"
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
		results.m_result_string = payload->GetDescriptionComponent()->GetDescription();
	}
	else
	{
		results.m_result_string = SceneManager::GetInstance()->GetCurrentScene()->GetSceneDescription();
	}
}

bool LookAction::IsValidPayload(const SceneObject* payload) const
{
	return payload == nullptr || (payload != nullptr && payload->GetIsValid() && payload->GetDescriptionComponent() != nullptr);
}

bool LookAction::IsValidPayload(const std::vector<SceneObject*> payload) const
{
	return (payload.size() == 1 && IsValidPayload(payload[0])) || payload.size() == 0;
}

void LookAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot look at that.\n";
}
