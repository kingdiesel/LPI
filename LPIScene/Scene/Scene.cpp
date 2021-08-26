#include "Scene.h"

void Scene::AddSceneObject(SceneObject* scene_object)
{
	m_scene_objects.push_back(scene_object);
}
