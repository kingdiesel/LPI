#pragma once
// a component that allows a scene object to be the target of a use action
class UseComponent
{
public:
	UseComponent() = default;

	// usable accessors
	bool GetUsable() const;
	void SetUsable(const bool is_usable);
private:
	// is currently usable
	bool m_is_usable = true;
};