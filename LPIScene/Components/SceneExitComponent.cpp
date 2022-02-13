#include "SceneExitComponent.h"
#include "Scene/Scene.h"

SceneExitComponent::SceneExitComponent(Scene* scene_exit) :
	m_scene_exit(scene_exit)
{
}

void SceneExitComponent::SetSceneExit(Scene* scene_exit)
{
	m_scene_exit = scene_exit;
}

Scene* SceneExitComponent::GetSceneExit() const
{
	return m_scene_exit;
}
