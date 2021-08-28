#include "Scene.h"
#include "Objects/SceneObject.h"

void Scene::AddSceneObject(SceneObject* scene_object)
{
	m_scene_objects.push_back(scene_object);
}

SceneObject* Scene::FindByNoun(const std::string& noun)
{
	auto found_action = std::find_if(m_scene_objects.begin(), m_scene_objects.end(),
		[&noun](const SceneObject* object)
		{
			return object->MatchesNoun(noun);
		}
	);

	if (found_action != m_scene_objects.end())
	{
		return *found_action;
	}

	return nullptr;
}
