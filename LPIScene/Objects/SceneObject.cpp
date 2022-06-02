#include "SceneObject.h"
#include "Components/SceneExitComponent.h"
#include "Components/InventoryItemComponent.h"
#include "Components/UseComponent.h"
#include <cassert>

const std::string& SceneObject::GetID() const
{
	return m_id;
}

void SceneObject::SetID(const std::string& id)
{
	m_id = id;
}

bool SceneObject::operator==(const std::string& rhs) const
{
	return m_id == rhs;
}

bool SceneObject::operator==(const SceneObject& rhs) const
{
	return m_id == rhs.m_id;
}

bool SceneObject::MatchesNoun(const std::string& noun) const
{
	return std::find(m_nouns.begin(), m_nouns.end(), noun) != m_nouns.end();
}

bool SceneObject::MatchesAdjective(const std::string& adjective) const
{
	return std::find(m_adjectives.begin(), m_adjectives.end(), adjective) != m_adjectives.end();
}

bool SceneObject::MatchesAdjectiveNoun(const std::string& adjective, const std::string& noun) const
{
	return MatchesAdjective(adjective) && MatchesNoun(noun);
}

void SceneObject::AddNoun(const std::string& noun)
{
	m_nouns.push_back(noun);
}

void SceneObject::AddAdjective(const std::string& adjective)
{
	m_adjectives.push_back(adjective);
}

void SceneObject::SetParentScene(Scene* parent_scene)
{
	m_parent_scene = parent_scene;
}

Scene* SceneObject::GetParentScene() const
{
	return m_parent_scene;
}

std::string SceneObject::GetDebugName() const
{
	return "SceneObject";
}

const std::string& SceneObject::GetDescription() const
{
	return m_description;
}

void SceneObject::SetDescription(const std::string& description)
{
	m_description = description;
}

const std::string& SceneObject::GetShortName() const
{
	return m_short_name;
}

void SceneObject::SetShortName(const std::string & short_name)
{
	m_short_name = short_name;
}

void SceneObject::SetIsValid(const bool is_valid)
{
	m_is_valid = is_valid;
}

bool SceneObject::GetIsValid() const
{
	return m_is_valid;
}

void SceneObject::AddSceneExitComponent()
{
	assert(m_exit_component == nullptr);
	m_exit_component = new SceneExitComponent();
}

const SceneExitComponent* SceneObject::GetSceneExitComponent() const
{
	return m_exit_component;
}

SceneExitComponent* SceneObject::GetSceneExitComponent()
{
	return m_exit_component;
}

void SceneObject::AddInventoryItemComponent()
{
	assert(m_inventory_item_component == nullptr);
	m_inventory_item_component = new InventoryItemComponent();
}

const InventoryItemComponent* SceneObject::GetInventoryItemComponent() const
{
	return m_inventory_item_component;
}

InventoryItemComponent* SceneObject::GetInventoryItemComponent()
{
	return m_inventory_item_component;
}

void SceneObject::AddUseComponent()
{
	m_use_component = new UseComponent();
}

const UseComponent* SceneObject::GetUseComponent() const
{
	return m_use_component;
}

UseComponent* SceneObject::GetUseComponent()
{
	return m_use_component;
}
