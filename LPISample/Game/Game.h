#pragma once
#include <vector>
#include "Scene/Scene.h"
#include "BNF/BNF.h"

class Game
{
public:
	void Init();
	const std::vector<class BaseAction*>& GetActions() const;
	void ProcessCommand(const std::string& command);
private:
	std::vector<class BaseAction*> m_actions;
	Scene m_main_scene;
	BNF m_grammar;
};