#pragma once
#include <vector>
#include <string>
#include <memory>
#include <mutex>
class Scene;
class SceneManager
{
public:
	static std::shared_ptr<SceneManager> GetInstance(void);
	void SetCurrentScene(Scene* current_scene);
	Scene* GetCurrentScene() const;

private:
	static std::shared_ptr<SceneManager> m_scene_manager;
	static std::once_flag m_scene_manager_once_flag;
	
	Scene* m_current_scene = nullptr;
};