#include "pch.h"
#include <gtest/gtest.h>
#include "Components/SceneExitComponent.cpp"

TEST(TestComponents, TestSceneExit)
{
	SceneExitComponent scene_exit_object;
	EXPECT_TRUE(scene_exit_object.GetSceneExit() == nullptr);
	
	Scene one;
	SceneExitComponent scene_exit_object2(&one);
	EXPECT_TRUE(scene_exit_object2.GetSceneExit() == &one);

}