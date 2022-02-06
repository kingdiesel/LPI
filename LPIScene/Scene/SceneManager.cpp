#include "SceneManager.h"

std::shared_ptr<SceneManager> SceneManager::m_scene_manager(nullptr);
std::once_flag SceneManager::m_scene_manager_once_flag;

std::shared_ptr<SceneManager> SceneManager::GetInstance(void)
{
	std::call_once(m_scene_manager_once_flag, []() { m_scene_manager.reset(new SceneManager); });
	return m_scene_manager;
}

void SceneManager::SetCurrentScene(Scene* current_scene)
{
	m_current_scene = current_scene;
}

Scene* SceneManager::GetCurrentScene() const
{
	return m_current_scene;
}

Scene* SceneManager::GetCharacterScene()
{
	return &m_character_scene;
}
