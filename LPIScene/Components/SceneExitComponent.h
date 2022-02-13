#pragma once
class Scene;
class SceneExitComponent
{
public:
	SceneExitComponent() = default;
	SceneExitComponent(Scene* scene_exit);

	void SetSceneExit(Scene* scene_exit);
	Scene* GetSceneExit() const;
private:
	Scene* m_scene_exit = nullptr;
};