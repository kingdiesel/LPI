#pragma once
#include <vector>
#include <string>

class SceneObject;
class Scene
{
public:
	Scene() = default;
	void AddSceneObject(SceneObject* scene_object);
	SceneObject* FindByNoun(const std::string& noun);
	void SetSceneDescription(const std::string& description);
	std::string GetSceneDescription() const;
private:
	std::vector<SceneObject*> m_scene_objects;
	std::string m_scene_description;
};