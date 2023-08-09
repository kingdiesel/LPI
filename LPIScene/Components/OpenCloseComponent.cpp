#include "OpenCloseComponent.h"

void OpenCloseComponent::SetIsOpen(const bool is_open)
{
	m_open = is_open;
}

bool OpenCloseComponent::IsOpen() const
{
	return m_open;
}
