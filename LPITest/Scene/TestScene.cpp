#include "pch.h"
#include <gtest/gtest.h>
#include "Scene/Scene.cpp"
#include "Scene/SceneManager.cpp"

TEST(TestScene, TestScene)
{
	SceneObject scene_object;
	scene_object.SetID("one");
	scene_object.SetDescription("a thing");
	scene_object.AddNoun("FROG");

	Scene scene;
	scene.AddSceneObject(&scene_object);

	EXPECT_TRUE(scene.FindByNoun("FROG") != nullptr);
	EXPECT_TRUE(scene.FindByID("one") != nullptr);
	EXPECT_TRUE(scene_object.GetParentScene() == &scene);
	
	SceneObject* removed_object = scene.RemoveSceneObject("one");
	EXPECT_TRUE(scene_object.GetParentScene() == nullptr);
	EXPECT_TRUE(removed_object->GetID() == "one");

	removed_object = scene.RemoveSceneObject("one");
	EXPECT_TRUE(removed_object == nullptr);
}

TEST(TestScene, TestSceneManager)
{
	Scene scene;
	EXPECT_TRUE(SceneManager::GetInstance() != nullptr);
	EXPECT_TRUE(SceneManager::GetInstance()->GetCurrentScene() == nullptr);
	
	SceneManager::GetInstance()->SetCurrentScene(&scene);

	EXPECT_TRUE(SceneManager::GetInstance()->GetCurrentScene() == &scene);
}

TEST(TestScene, TestSceneExit)
{
	Scene scene;
	
	Scene other_scene;
}