#pragma once
#include <vector>
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "BNF/BNF.h"

class Game
{
public:
	void Init();
	const std::vector<class BaseAction*>& GetActions() const;
	void ProcessCommand(const std::string& command);
private:
	void SceneChangeCallback(SceneObject* payload, Scene* source, Scene* destination);
	UseResults ObjectUsedCallback(SceneObject* payload, SceneObject* payload2);
	std::vector<class BaseAction*> m_actions;
	Scene m_main_scene;
	Scene m_north_scene;
	BNF m_grammar;

	// game specific
	bool m_picked_up_tissue = false;
	bool m_picked_up_key = false;
};