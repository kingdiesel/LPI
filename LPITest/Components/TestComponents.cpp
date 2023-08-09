#include "pch.h"
#include <gtest/gtest.h>
#include "Components/SceneExitComponent.cpp"
#include "Components/InventoryItemComponent.cpp"
#include "Components/UseComponent.cpp"
#include "Components/DescriptionComponent.cpp"
#include "Components/OpenCloseComponent.cpp"
#include "Components/InventoryItemContainerComponent.cpp"
TEST(TestComponents, TestSceneExit)
{
	SceneExitComponent scene_exit_object;
	EXPECT_TRUE(scene_exit_object.GetSceneExit() == nullptr);
	
	Scene one;
	SceneExitComponent scene_exit_object2(&one);
	EXPECT_TRUE(scene_exit_object2.GetSceneExit() == &one);
}


TEST(TestComponents, TestDescription)
{
	DescriptionComponent description_component;
	EXPECT_TRUE(description_component.GetDescription() == "");

	description_component.SetDescription("a thing");
	EXPECT_TRUE(description_component.GetDescription() == "a thing");
}

TEST(TestComponents, TestInventoryItemComponent)
{
	//InventoryItemComponent inventory_component;
}

TEST(TestComponents, TestInventoryItemContainerComponent)
{
	InventoryItemContainerComponent inventory_container_component;

	EXPECT_TRUE(inventory_container_component.GetItemCount() == 0);
	EXPECT_FALSE(inventory_container_component.HasItem("some_id"));

	std::unique_ptr<SceneObject> scene_object = std::make_unique<SceneObject>();
	scene_object->SetID("some_id");

	inventory_container_component.AddItem(std::move(scene_object));
	EXPECT_TRUE(inventory_container_component.GetItemCount() == 1);
	EXPECT_TRUE(inventory_container_component.HasItem("some_id"));

	std::unique_ptr<SceneObject> scene_object_two = std::make_unique<SceneObject>();
	scene_object_two->SetID("some_other_id");

	inventory_container_component.AddItem(std::move(scene_object_two));
	EXPECT_TRUE(inventory_container_component.GetItemCount() == 2);
	EXPECT_TRUE(inventory_container_component.HasItem("some_id"));
	EXPECT_TRUE(inventory_container_component.HasItem("some_other_id"));

	std::unique_ptr<SceneObject> removed_scene_object = inventory_container_component.RemoveItem("some_id");
	EXPECT_TRUE(removed_scene_object != nullptr);
	EXPECT_TRUE(removed_scene_object->GetID() == "some_id");
	EXPECT_TRUE(inventory_container_component.GetItemCount() == 1);
	EXPECT_FALSE(inventory_container_component.HasItem("some_id"));
	EXPECT_TRUE(inventory_container_component.HasItem("some_other_id"));

	std::unique_ptr<SceneObject> removed_scene_object_two = inventory_container_component.RemoveItem("none");
	EXPECT_TRUE(inventory_container_component.GetItemCount() == 1);
	EXPECT_TRUE(removed_scene_object_two == nullptr);

	removed_scene_object_two = inventory_container_component.RemoveItem("some_other_id");
	EXPECT_TRUE(removed_scene_object_two != nullptr);
	EXPECT_TRUE(removed_scene_object_two->GetID() == "some_other_id");
	EXPECT_TRUE(inventory_container_component.GetItemCount() == 0);
}

TEST(TestComponents, TestOpenCloseComponent)
{
	OpenCloseComponent open_component;
	EXPECT_FALSE(open_component.IsOpen());

	open_component.SetIsOpen(true);
	EXPECT_TRUE(open_component.IsOpen());

	open_component.SetIsOpen(false);
	EXPECT_FALSE(open_component.IsOpen());
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