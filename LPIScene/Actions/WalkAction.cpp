#include "WalkAction.h"
#include "Objects/SceneExitObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

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
	if (SceneExitObject* scene_exit = dynamic_cast<SceneExitObject*>(payload))
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
	if (SceneExitObject* scene_exit = dynamic_cast<SceneExitObject*>(payload))
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
