#pragma once
#include "SceneObject.h"
class Scene;
class SceneInventoryObject : public SceneObject
{
public:
	SceneInventoryObject() = default;
	virtual std::string GetDebugName() const override;

	bool IsDestroyedOnUse() const;
	void SetIsDestroyedOnUse(const bool destroyed);

private:
	bool m_destroy_upon_use = false;
};