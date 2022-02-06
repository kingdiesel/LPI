#include "SceneInventoryObject.h"

std::string SceneInventoryObject::GetDebugName() const
{
	return "SceneInventoryObject";
}

bool SceneInventoryObject::IsDestroyedOnUse() const
{
	return m_destroy_upon_use;
}

void SceneInventoryObject::SetIsDestroyedOnUse(const bool destroyed)
{
	m_destroy_upon_use = destroyed;
}
