#pragma once
#include "BaseAction.h"
/*
	Action used to print descriptions of scene objects
*/
class LookAction : public BaseAction
{
public:
	LookAction();

	// Inherited via BaseAction
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(const SceneObject* payload) const override;
	virtual bool IsValidPayload(const std::vector<SceneObject*> payload) const override;

	virtual void GetFailedActionMessage(std::string& message) override;
};