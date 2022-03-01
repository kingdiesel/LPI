#pragma once
class Scene;
// this component allows scene objects to be used as scene exits
class SceneExitComponent
{
public:
	SceneExitComponent() = default;
	SceneExitComponent(Scene* scene_exit);

	// scene exit accessors
	void SetSceneExit(Scene* scene_exit);
	Scene* GetSceneExit() const;
private:

	// exiting via this component leads to this scene
	Scene* m_scene_exit = nullptr;
};