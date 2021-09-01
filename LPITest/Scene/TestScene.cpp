#include "pch.h"
#include <gtest/gtest.h>
#include "Scene/Scene.cpp"

TEST(TestScene, TestScene)
{
	SceneObject scene_object;
	scene_object.SetID("one");
	scene_object.SetDescription("a thing");
	scene_object.AddNoun("FROG");

	Scene scene;
	scene.AddSceneObject(&scene_object);

	EXPECT_TRUE(scene.FindByNoun("FROG") != nullptr);
}