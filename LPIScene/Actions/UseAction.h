#pragma once
#include "BaseAction.h"
/*
	Action for item use
*/
class UseAction : public BaseAction
{
public:
	UseAction();

	// Inherited via BaseAction
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(SceneObject* payload) override;
	virtual bool IsValidPayload(std::vector<SceneObject*> payload) override;

	virtual void GetFailedActionMessage(std::string& message) override;
};