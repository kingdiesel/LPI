#pragma once
#include "BaseAction.h"
/*
	Pick up action used to put an item in the character inventory
*/
class PickupAction : public BaseAction
{
public:
	PickupAction();

	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(SceneObject* payload) override;
	virtual bool IsValidPayload(std::vector<SceneObject*> payload) override;

	// Inherited via BaseAction
	virtual void GetFailedActionMessage(std::string& message) override;
};