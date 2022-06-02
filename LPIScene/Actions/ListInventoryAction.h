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

	virtual bool IsValidPayload(const SceneObject* payload) const override;
	virtual bool IsValidPayload(const std::vector<SceneObject*> payload) const override;

	static std::string GetEmptyInventoryString();

	virtual void GetFailedActionMessage(std::string& message) override;
};