#include "Scene.h"
#include "Objects/SceneObject.h"
#include <cassert>

const std::string& Scene::GetID() const
{
	return m_id;
}

void Scene::SetID(const std::string& id)
{
	m_id = id;
}

void Scene::AddSceneObject(SceneObject* scene_object)
{
	assert(scene_object != nullptr);
	assert(scene_object->GetParentScene() == nullptr);
	m_scene_objects.push_back(scene_object);
	scene_object->SetParentScene(this);
}

SceneObject* Scene::RemoveSceneObject(const std::string& id)
{
	// find object by id
	auto found_object = std::remove_if(m_scene_objects.begin(), m_scene_objects.end(),
		[&id](const SceneObject* object)
		{
			return object->GetID() == id;
		}
	);

	// if we find an object unparent it
	SceneObject* return_value = found_object == m_scene_objects.end() ? nullptr : *found_object;
	if (return_value != nullptr)
	{
		return_value->SetParentScene(nullptr);
	}

	// remove from list
	m_scene_objects.erase(found_object, m_scene_objects.end());
	return return_value;
}

SceneObject* Scene::FindByNoun(const std::string& noun)
{
	auto found_object = std::find_if(m_scene_objects.begin(), m_scene_objects.end(),
		[&noun](const SceneObject* object)
		{
			return object->MatchesNoun(noun);
		}
	);

	if (found_object != m_scene_objects.end())
	{
		return *found_object;
	}

	return nullptr;
}
SceneObject* Scene::FindByID(const std::string& ID)
{
	auto found_object = std::find_if(m_scene_objects.begin(), m_scene_objects.end(),
		[&ID](const SceneObject* object)
		{
			return object->GetID() == ID;
		}
	);

	if (found_object != m_scene_objects.end())
	{
		return *found_object;
	}

	return nullptr;
}

void Scene::SetSceneDescription(const std::string& description)
{
	m_scene_description = description;
}

std::string Scene::GetSceneDescription() const
{
	return m_scene_description;
}
