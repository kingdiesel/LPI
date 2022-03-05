#pragma once
// a component that allows a scene object to be the target of a use action
class UseComponent
{
public:
	UseComponent() = default;

	// usable accessors
	bool GetUsable() const;
	void SetUsable(const bool is_usable);

	// destroy on use accessors
	bool GetDestroyOnUse() const;
	void SetDestroyOnUse(const bool destroy_on_use);
private:
	// is currently usable
	bool m_is_usable = true;

	// should it be destroyed once used.
	bool m_destroy_on_use = false;
};