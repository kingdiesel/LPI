#pragma once
#include "SceneObject.h"
class Scene;
class SceneExitObject : public SceneObject
{
public:
	SceneExitObject() = default;
	SceneExitObject(Scene* scene_exit);

	void SetSceneExit(Scene* scene_exit);
	Scene* GetSceneExit() const;

	virtual std::string GetDebugName() const override;
private:
	Scene* m_scene_exit = nullptr;
};