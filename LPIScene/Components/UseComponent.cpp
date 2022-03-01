#include "UseComponent.h"

bool UseComponent::GetUsable() const
{
	return m_is_usable;
}

void UseComponent::SetUsable(const bool is_usable)
{
	m_is_usable = is_usable;
}
