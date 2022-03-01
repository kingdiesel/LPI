#pragma once
// a component that allows a scene object to enter the player's inventory
class InventoryItemComponent
{
public:
	InventoryItemComponent() = default;

	// destroy on use accessors
	bool GetDestroyOnUse() const;
	void SetDestroyOnUse(const bool destroy_on_use);

private:
	// if this inventory item is usable, should it be destroyed once used.
	bool m_destroy_on_use = false;
};