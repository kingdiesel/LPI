#pragma once
#include <vector>
#include <string>
#include <map>

class SceneObject;
/*
	A container for scene objects with a description
*/
class Scene
{
public:
	Scene() = default;

	// add an object to the scene
	void AddSceneObject(SceneObject* scene_object);
	SceneObject* RemoveSceneObject(const std::string& id);

	// find a scene object
	SceneObject* FindByNoun(const std::string& noun);
	SceneObject* FindByID(const std::string& ID);
	
	// scene description accessors
	void SetSceneDescription(const std::string& description);
	std::string GetSceneDescription() const;

private:
	// the scene objects in this scene
	std::vector<SceneObject*> m_scene_objects;

	// the scene description
	std::string m_scene_description;
};