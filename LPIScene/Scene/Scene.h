#pragma once
#include <vector>

class SceneObject;
class Scene
{
public:
	Scene() = default;
	void AddSceneObject(SceneObject* scene_object);
private:
	std::vector<SceneObject*> m_scene_objects;
};