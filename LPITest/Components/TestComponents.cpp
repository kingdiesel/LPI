#include "pch.h"
#include <gtest/gtest.h>
#include "Components/SceneExitComponent.cpp"
#include "Components/InventoryItemComponent.cpp"
#include "Components/UseComponent.cpp"
#include "Components/DescriptionComponent.cpp"

TEST(TestComponents, TestSceneExit)
{
	SceneExitComponent scene_exit_object;
	EXPECT_TRUE(scene_exit_object.GetSceneExit() == nullptr);
	
	Scene one;
	SceneExitComponent scene_exit_object2(&one);
	EXPECT_TRUE(scene_exit_object2.GetSceneExit() == &one);
}


TEST(TestObjects, TestDescription)
{
	DescriptionComponent description_component;
	description_component.SetDescription("a thing");
	EXPECT_TRUE(description_component.GetDescription() == "a thing");
}

TEST(TestComponents, TestInventoryItemComponent)
{
	//InventoryItemComponent inventory_component;
}

TEST(TestComponents, TestUseComponent)
{
	UseComponent usable_component;

	usable_component.SetUsable(false);
	EXPECT_FALSE(usable_component.GetUsable());

	usable_component.SetUsable(true);
	EXPECT_TRUE(usable_component.GetUsable());

	usable_component.SetDestroyOnUse(false);
	EXPECT_FALSE(usable_component.GetDestroyOnUse());

	usable_component.SetDestroyOnUse(true);
	EXPECT_TRUE(usable_component.GetDestroyOnUse());
}