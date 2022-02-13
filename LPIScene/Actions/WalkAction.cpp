#include "WalkAction.h"
#include "Components/SceneExitComponent.h"
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
	if (SceneExitComponent* scene_exit = payload->GetSceneExitComponent())
	{
		results.m_success = true;
		if (Scene* next_scene = scene_exit->GetSceneExit())
		{
			SceneManager::GetInstance()->SetCurrentScene(next_scene);
			results.m_result_string = next_scene->GetSceneDescription();
		}
	}
}

bool WalkAction::IsValidPayload(SceneObject* payload)
{
	if (SceneExitComponent* scene_exit = payload->GetSceneExitComponent())
	{
		return true;
	}
	return false;
}

bool WalkAction::IsValidPayload(std::vector<SceneObject*> payload)
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
