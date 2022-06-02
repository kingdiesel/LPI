#pragma once
#include "BaseAction.h"
/*
	Walk action used to traverse between scenes
*/
class WalkAction : public BaseAction
{
public:
	WalkAction();

	// Inherited via BaseAction
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(const SceneObject* payload) const override;
	virtual bool IsValidPayload(const std::vector<SceneObject*> payload) const override;

	virtual void GetFailedActionMessage(std::string& message) override;
};