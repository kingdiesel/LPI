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
private:
	std::vector<SceneObject*> m_scene_objects;
};