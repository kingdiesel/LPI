#pragma once
#include "BaseAction.h"
/*
	Walk action used to traverse between scenes
*/
class WalkAction : public BaseAction
{
public:
	WalkAction();

	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(SceneObject* payload) override;
	virtual bool IsValidPayload(std::vector<SceneObject*> payload) override;

	// Inherited via BaseAction
	virtual void GetFailedActionMessage(std::string& message) override;
};