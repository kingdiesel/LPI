#pragma once
#include "BaseAction.h"
/*
	Pick up action used to put an item in the character inventory
*/
class PickupAction : public BaseAction
{
public:
	PickupAction();

	// Inherited via BaseAction
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(const SceneObject* payload) const override;
	virtual bool IsValidPayload(const std::vector<SceneObject*> payload) const override;

	virtual void GetFailedActionMessage(std::string& message) override;
};