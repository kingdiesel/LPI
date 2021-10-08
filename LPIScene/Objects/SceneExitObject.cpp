#include "SceneExitObject.h"
#include "Scene/Scene.h"

SceneExitObject::SceneExitObject(Scene* scene_exit) :
	m_scene_exit(scene_exit)
{
}

void SceneExitObject::SetSceneExit(Scene* scene_exit)
{
	m_scene_exit = scene_exit;
}

Scene* SceneExitObject::GetSceneExit() const
{
	return m_scene_exit;
}

std::string SceneExitObject::GetDebugName() const
{
	return "SceneExitObject";
}
