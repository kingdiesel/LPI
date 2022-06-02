#include "DescriptionComponent.h"

const std::string& DescriptionComponent::GetDescription() const
{
	return m_description;
}

void DescriptionComponent::SetDescription(const std::string& description)
{
	m_description = description;
}
