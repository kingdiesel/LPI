#include "WalkAction.h"
#include "Components/SceneExitComponent.h"
#include "Components/DescriptionComponent.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Objects/SceneObject.h"

WalkAction::WalkAction()
{
	AddVerb("WALK");
	AddVerb("GO");
}

void WalkAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	if (payload.size() == 1)
	{
		return Execute(payload[0], results);
	}
}

void WalkAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	results.m_success = false;
	if (const SceneExitComponent* scene_exit = payload->GetSceneExitComponent())
	{
		results.m_success = true;
		if (Scene* next_scene = scene_exit->GetSceneExit())
		{
			SceneManager::GetInstance()->SetCurrentScene(next_scene);
			results.m_result_string = next_scene->GetDescriptionComponent()->GetDescription();
		}
	}
}

bool WalkAction::IsValidPayload(const SceneObject* payload) const
{
	return payload != nullptr && payload->GetIsValid() &&
		payload->GetSceneExitComponent() != nullptr && payload->GetSceneExitComponent()->GetSceneExit()->GetDescriptionComponent() != nullptr;
}

bool WalkAction::IsValidPayload(const std::vector<SceneObject*> payload) const
{
	if (payload.size() == 1)
	{
		return IsValidPayload(payload[0]);
	}
	return false;
}

void WalkAction::GetFailedActionMessage(std::string& message)
{
	message = "You cannot walk there.\n";
}
