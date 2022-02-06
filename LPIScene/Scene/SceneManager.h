#pragma once
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include "Scene.h"

/*
	Global singleton for scene management. Contains the currently active scene
	and the global main character scene.
*/
class SceneManager
{
public:
	// get the scene manager singleton
	static std::shared_ptr<SceneManager> GetInstance(void);
	
	// current scene accesssors
	void SetCurrentScene(Scene* current_scene);
	Scene* GetCurrentScene() const;

	// get the character scene
	Scene* GetCharacterScene();

private:
	// internal singleton variables
	static std::shared_ptr<SceneManager> m_scene_manager;
	static std::once_flag m_scene_manager_once_flag;
	
	// the current active scene
	Scene* m_current_scene = nullptr;
	
	// the scene attached to the main character
	Scene m_character_scene;
};