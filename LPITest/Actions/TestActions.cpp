#include "pch.h"
#include <gtest/gtest.h>
#include "Actions/BaseAction.cpp"
#include "Actions/LookAction.cpp"
#include "Actions/WalkAction.cpp"
#include "Actions/PickupAction.cpp"
#include "Actions/ListInventoryAction.cpp"
#include "Objects/SceneExitObject.cpp"

TEST(TestActions, TestBaseAction)
{
	SceneObject scene_object;
	scene_object.SetDescription("a thing");
	scene_object.SetID("one");

	LookAction look_action;
	EXPECT_TRUE(look_action.MatchesVerb("LOOK"));
	EXPECT_FALSE(look_action.MatchesVerb("EXAMINE"));
	look_action.AddVerb("EXAMINE");
	EXPECT_TRUE(look_action.MatchesVerb("EXAMINE"));
}

TEST(TestActions, TestLookAction)
{
	SceneObject scene_object;
	scene_object.SetDescription("a thing");
	scene_object.SetID("one");

	LookAction look_action;
	ExecuteResults results;
	look_action.Execute(&scene_object, results);
	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(results.m_result_string == "a thing");
}

TEST(TestActions, TestListInventoryAction)
{
	SceneObject scene_object;
	scene_object.SetDescription("a thing");
	scene_object.SetID("one");

	ListInventoryAction list_inventory_action;
	ExecuteResults results;
	list_inventory_action.Execute(nullptr, results);
	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(results.m_result_string == ListInventoryAction::GetEmptyInventoryString());

	SceneManager::GetInstance()->GetCharacterScene()->AddSceneObject(&scene_object);
	list_inventory_action.Execute(nullptr, results);
	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(results.m_result_string != ListInventoryAction::GetEmptyInventoryString());
	SceneManager::GetInstance()->GetCharacterScene()->RemoveSceneObject("one");
}

TEST(TestActions, TestWalkAction)
{
	Scene one_scene, two_scene;
	SceneExitObject one_to_two(&two_scene);
	SceneExitObject two_to_one(&one_scene);
	one_scene.AddSceneObject(&one_to_two);
	two_scene.AddSceneObject(&two_to_one);
	SceneManager::GetInstance()->SetCurrentScene(&one_scene);
	
	WalkAction walk_action;
	ExecuteResults results;

	walk_action.Execute(&one_to_two, results);
	EXPECT_TRUE(SceneManager::GetInstance()->GetCurrentScene() == &two_scene);
	
	walk_action.Execute(&two_to_one, results);
	EXPECT_TRUE(SceneManager::GetInstance()->GetCurrentScene() == &one_scene);

	SceneManager::GetInstance()->SetCurrentScene(nullptr);
}

void SceneChangeTest(SceneObject* payload, Scene* source, Scene* destination)
{
	EXPECT_TRUE(payload->GetID() == "one");
	EXPECT_TRUE(source->GetID() == "TestPickupActionScene");
	EXPECT_TRUE(destination->GetID() == "INVENTORY_SCENE");
}
TEST(TestActions, TestPickupAction)
{
	SceneObject scene_object;
	scene_object.SetDescription("a thing of the past");
	scene_object.SetShortName("a thing");
	scene_object.SetID("one");
	scene_object.AddNoun("thing");

	Scene scene;
	scene.AddSceneObject(&scene_object);
	scene.SetID("TestPickupActionScene");

	SceneManager::GetInstance()->m_scene_change_cb = SceneChangeTest;

	PickupAction pickup_action;
	ExecuteResults results;
	pickup_action.Execute(&scene_object, results);
	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(SceneManager::GetInstance()->GetCharacterScene()->FindByNoun("thing") == &scene_object);
	EXPECT_TRUE(scene_object.GetParentScene() == SceneManager::GetInstance()->GetCharacterScene());
	EXPECT_TRUE(scene.FindByNoun("thing") == nullptr);

	SceneManager::GetInstance()->m_scene_change_cb = nullptr;
}