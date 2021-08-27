#pragma once
#include "BaseAction.h"

class LookAction : public BaseAction
{
public:
	LookAction();

	// Inherited via BaseAction
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
};