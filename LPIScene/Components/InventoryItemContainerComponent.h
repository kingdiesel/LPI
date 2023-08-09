#pragma once
#include <vector>
#include <memory>
#include <string>

// a component that contains a list of scene objects for storage and removal
class SceneObject;
class InventoryItemContainerComponent
{
public:
	InventoryItemContainerComponent() = default;

	void AddItem(std::unique_ptr<SceneObject> item);
	std::unique_ptr<SceneObject> RemoveItem(const std::string& id);

	int GetItemCount() const;
	bool HasItem(const std::string& id) const;

private:
	std::vector<std::unique_ptr<SceneObject>> m_items;
};