#pragma once
#include <string>
// a component that allows a scene object to enter the player's inventory
class DescriptionComponent
{
public:
	DescriptionComponent() = default;

	const std::string& GetDescription() const;
	void SetDescription(const std::string& description);

private:
	std::string m_description;
};