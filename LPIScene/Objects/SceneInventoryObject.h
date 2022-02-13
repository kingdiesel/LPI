#pragma once
#include "SceneObject.h"
class Scene;
class SceneInventoryObject : public SceneObject
{
public:
	SceneInventoryObject() = default;
	virtual std::string GetDebugName() const override;
};