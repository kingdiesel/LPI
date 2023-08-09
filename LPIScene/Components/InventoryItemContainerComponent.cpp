#include "InventoryItemContainerComponent.h"
#include "Objects/SceneObject.h"

void InventoryItemContainerComponent::AddItem(std::unique_ptr<SceneObject> item)
{
	m_items.push_back(std::move(item));
}

std::unique_ptr<SceneObject> InventoryItemContainerComponent::RemoveItem(const std::string& id)
{
    auto iter = std::find_if(m_items.begin(), m_items.end(),
        [&id](const std::unique_ptr<SceneObject>& item) 
        {
            return item != nullptr && item->GetID() == id;
        }
    );

    if (iter != m_items.end())
    {
        std::unique_ptr<SceneObject> found_item = std::move(*iter);
        m_items.erase(iter);
        return found_item;
    }

    return nullptr;
}

int InventoryItemContainerComponent::GetItemCount() const
{
    return static_cast<int>(m_items.size());
}

bool InventoryItemContainerComponent::HasItem(const std::string& id) const
{
    auto iter = std::find_if(m_items.begin(), m_items.end(),
        [&id](const std::unique_ptr<SceneObject>& item)
        {
            return item != nullptr && item->GetID() == id;
        }
    );

    return iter != m_items.end();
}
