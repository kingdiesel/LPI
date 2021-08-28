#pragma once
#include "BaseAction.h"

class LookAction : public BaseAction
{
public:
	LookAction();

	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;
};