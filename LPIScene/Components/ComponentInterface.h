#pragma once
// a component that allows a scene object to enter the player's inventory
class ComponentInterface
{
public:
	// component API
	void AddSceneExitComponent();
	const class SceneExitComponent* GetSceneExitComponent() const;
	class SceneExitComponent* GetSceneExitComponent();

	void AddInventoryItemComponent();
	const class InventoryItemComponent* GetInventoryItemComponent() const;
	class InventoryItemComponent* GetInventoryItemComponent();

	void AddUseComponent();
	const class UseComponent* GetUseComponent() const;
	class UseComponent* GetUseComponent();

	void AddDescriptionComponent();
	const class DescriptionComponent* GetDescriptionComponent() const;
	class DescriptionComponent* GetDescriptionComponent();

protected:
	// Component list
	class SceneExitComponent* m_exit_component = nullptr;
	class InventoryItemComponent* m_inventory_item_component = nullptr;
	class UseComponent* m_use_component = nullptr;
	class DescriptionComponent* m_description_component = nullptr;
};