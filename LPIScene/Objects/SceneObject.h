#pragma once
#include <string>
#include <vector>

class Scene;
class SceneObject
{
public:
	SceneObject() = default;

	// globally unique identifier for this scene object
	const std::string& GetID() const;
	void SetID(const std::string& id);

	// description of this scene object
	const std::string& GetDescription() const;
	void SetDescription(const std::string& description);

	// short name of this scene object
	const std::string& GetShortName() const;
	void SetShortName(const std::string & short_name);

	// compare two scene objects
	bool operator==(const std::string& rhs) const;
	bool operator==(const SceneObject& rhs) const;

	// does this scene object's nouns match this noun
	bool MatchesNoun(const std::string& noun) const;
	
	// does this scene object's nouns match this adjective
	bool MatchesAdjective(const std::string& adjective) const;

	// does this scene object's adjective/nouns match these nouns/adjectives
	bool MatchesAdjectiveNoun(const std::string& adjective, const std::string& noun) const;

	// add noun descriptor for this object
	void AddNoun(const std::string& noun);

	// add adjective descriptor for this object
	void AddAdjective(const std::string& adjective);

	// parent scene accessors
	void SetParentScene(Scene* parent_scene);
	Scene* GetParentScene() const;

	// validity accessors
	void SetIsValid(const bool is_valid);
	bool GetIsValid() const;

	// developer facing name
	virtual std::string GetDebugName() const;

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

private:
	// globally unique identifier for this scene object
	std::string m_id;

	// description of this scene object, used for the look action
	std::string m_description;

	// short name of this scene object
	std::string m_short_name;

	// noun descriptors for this scene object
	std::vector<std::string> m_nouns;

	// adjective descriptors for this scene object
	std::vector<std::string> m_adjectives;

	// parent scene (can be null)
	Scene* m_parent_scene = nullptr;

	// is this still object still valid, not destroyed
	bool m_is_valid = true;

	// Component list
	class SceneExitComponent* m_exit_component = nullptr;
	class InventoryItemComponent* m_inventory_item_component = nullptr;
	class UseComponent* m_use_component = nullptr;
};