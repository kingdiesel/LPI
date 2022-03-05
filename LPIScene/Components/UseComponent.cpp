#include "UseComponent.h"

bool UseComponent::GetUsable() const
{
	return m_is_usable;
}

void UseComponent::SetUsable(const bool is_usable)
{
	m_is_usable = is_usable;
}

bool UseComponent::GetDestroyOnUse() const
{
	return m_destroy_on_use;
}

void UseComponent::SetDestroyOnUse(const bool destroy_on_use)
{
	m_destroy_on_use = destroy_on_use;
}
