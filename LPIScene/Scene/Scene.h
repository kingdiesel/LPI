#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Components/ComponentInterface.h"

class SceneObject;
/*
	A container for scene objects with a description
*/
class Scene : public ComponentInterface
{
public:
	Scene() = default;

	// globally unique identifier for this scene
	const std::string& GetID() const;
	void SetID(const std::string& id);

	// add an object to the scene
	void AddSceneObject(SceneObject* scene_object);
	SceneObject* RemoveSceneObject(const std::string& id);

	// find a scene object
	SceneObject* FindByNoun(const std::string& noun);
	SceneObject* FindByID(const std::string& ID);
	
	// full scene object list accessor
	const std::vector<SceneObject*> GetSceneObjects() const;

private:
	// the scene objects in this scene
	std::vector<SceneObject*> m_scene_objects;

	// the scene description
	std::string m_scene_description;

	// globally unique identifier for this scene
	std::string m_id;
};