#include "InventoryItemComponent.h"

bool InventoryItemComponent::GetDestroyOnUse() const
{
	return m_destroy_on_use;
}

void InventoryItemComponent::SetDestroyOnUse(const bool destroy_on_use)
{
	m_destroy_on_use = destroy_on_use;
}
