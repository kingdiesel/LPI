#pragma once
#include "BaseAction.h"
/*
	Action used to list inventory
*/
class ListInventoryAction : public BaseAction
{
public:
	ListInventoryAction();

	// Inherited via BaseAction
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) override;
	virtual void Execute(SceneObject* payload, ExecuteResults& results) override;

	virtual bool IsValidPayload(SceneObject* payload) override;
	virtual bool IsValidPayload(std::vector<SceneObject*> payload) override;

	static std::string GetEmptyInventoryString();

	virtual void GetFailedActionMessage(std::string& message) override;
};