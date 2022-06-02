#include "ComponentInterface.h"
#include "Components/SceneExitComponent.h"
#include "Components/InventoryItemComponent.h"
#include "Components/UseComponent.h"
#include "Components/DescriptionComponent.h"
#include <cassert>

void ComponentInterface::AddSceneExitComponent()
{
	assert(m_exit_component == nullptr);
	m_exit_component = new SceneExitComponent();
}

const SceneExitComponent* ComponentInterface::GetSceneExitComponent() const
{
	return m_exit_component;
}

SceneExitComponent* ComponentInterface::GetSceneExitComponent()
{
	return m_exit_component;
}

void ComponentInterface::AddInventoryItemComponent()
{
	assert(m_inventory_item_component == nullptr);
	m_inventory_item_component = new InventoryItemComponent();
}

const InventoryItemComponent* ComponentInterface::GetInventoryItemComponent() const
{
	return m_inventory_item_component;
}

InventoryItemComponent* ComponentInterface::GetInventoryItemComponent()
{
	return m_inventory_item_component;
}

void ComponentInterface::AddDescriptionComponent()
{
	m_description_component = new DescriptionComponent();
}

const DescriptionComponent* ComponentInterface::GetDescriptionComponent() const
{
	return m_description_component;
}

DescriptionComponent* ComponentInterface::GetDescriptionComponent()
{
	return m_description_component;
}

void ComponentInterface::AddUseComponent()
{
	m_use_component = new UseComponent();
}

const UseComponent* ComponentInterface::GetUseComponent() const
{
	return m_use_component;
}

UseComponent* ComponentInterface::GetUseComponent()
{
	return m_use_component;
}
