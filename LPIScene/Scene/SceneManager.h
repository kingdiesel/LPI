#pragma once
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include "Scene.h"
/*
	Use object result struct, a return value from the use function to 
	all the scene to fill custom use responses and reject uses based
	on scene state
*/
struct UseResults
{
	// did the action succeed
	bool m_success = false;

	// user facing result string
	std::string m_result_string;
};

/*
	Global singleton for scene management. Contains the currently active scene
	and the global main character scene.
*/
class SceneManager
{
public:
	SceneManager();

	// get the scene manager singleton
	static std::shared_ptr<SceneManager> GetInstance(void);
	
	// current scene accesssors
	void SetCurrentScene(Scene* current_scene);
	Scene* GetCurrentScene() const;

	// get the character scene
	Scene* GetCharacterScene();

	// callback function when objects change their scene parents
	std::function<void(SceneObject*, Scene*, Scene*)> m_scene_change_cb;
	
	// callback function when an object is used, second object will be nullptr
	// if it's a unary use
	std::function<UseResults(SceneObject*, SceneObject*)> m_scene_object_used_cb;

private:
	// internal singleton variables
	static std::shared_ptr<SceneManager> m_scene_manager;
	static std::once_flag m_scene_manager_once_flag;
	
	// the current active scene
	Scene* m_current_scene = nullptr;
	
	// the scene attached to the main character
	Scene m_character_scene;
};