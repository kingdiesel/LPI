#include "pch.h"
#include <gtest/gtest.h>
#include "Actions/BaseAction.cpp"
#include "Actions/LookAction.cpp"
#include "Actions/WalkAction.cpp"
#include "Actions/PickupAction.cpp"
#include "Actions/UseAction.cpp"
#include "Actions/ListInventoryAction.cpp"

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
	EXPECT_TRUE(look_action.IsValidPayload(&scene_object));
	EXPECT_TRUE(look_action.IsValidPayload(nullptr));
	scene_object.SetIsValid(false);
	EXPECT_FALSE(look_action.IsValidPayload(&scene_object));
	scene_object.SetIsValid(true);
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
	EXPECT_TRUE(list_inventory_action.IsValidPayload(nullptr));
	EXPECT_TRUE(list_inventory_action.IsValidPayload(std::vector<SceneObject*>()));

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
	SceneObject one_to_two;
	one_to_two.AddSceneExitComponent();
	one_to_two.GetSceneExitComponent()->SetSceneExit(&two_scene);
	SceneObject two_to_one;
	two_to_one.AddSceneExitComponent();
	two_to_one.GetSceneExitComponent()->SetSceneExit(&one_scene);
	one_scene.AddSceneObject(&one_to_two);
	two_scene.AddSceneObject(&two_to_one);
	SceneObject non_exit;
	SceneManager::GetInstance()->SetCurrentScene(&one_scene);
	
	WalkAction walk_action;
	ExecuteResults results;

	EXPECT_TRUE(walk_action.IsValidPayload(&one_to_two));
	EXPECT_FALSE(walk_action.IsValidPayload(&non_exit));
	one_to_two.SetIsValid(false);
	EXPECT_FALSE(walk_action.IsValidPayload(&one_to_two));
	one_to_two.SetIsValid(true);
	EXPECT_FALSE(walk_action.IsValidPayload(nullptr));

	walk_action.Execute(&one_to_two, results);
	EXPECT_TRUE(SceneManager::GetInstance()->GetCurrentScene() == &two_scene);
	
	EXPECT_TRUE(walk_action.IsValidPayload(&two_to_one));
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
	scene_object.AddInventoryItemComponent();
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
	EXPECT_TRUE(pickup_action.IsValidPayload(&scene_object));
	scene_object.SetIsValid(false);
	EXPECT_FALSE(pickup_action.IsValidPayload(&scene_object));
	scene_object.SetIsValid(true);
	EXPECT_FALSE(pickup_action.IsValidPayload(nullptr));
	pickup_action.Execute(&scene_object, results);

	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(SceneManager::GetInstance()->GetCharacterScene()->FindByNoun("thing") == &scene_object);
	EXPECT_TRUE(scene_object.GetParentScene() == SceneManager::GetInstance()->GetCharacterScene());
	EXPECT_TRUE(scene.FindByNoun("thing") == nullptr);

	SceneManager::GetInstance()->m_scene_change_cb = nullptr;
}

std::string ObjectUsedTest(SceneObject* payload, SceneObject* payload2)
{
	return "success";
}

TEST(TestActions, TestUseAction)
{
	SceneObject scene_object;
	scene_object.SetDescription("a thing of the past");
	scene_object.SetShortName("a thing");
	scene_object.SetID("one");
	scene_object.AddNoun("thing");

	Scene scene;
	scene.AddSceneObject(&scene_object);
	scene.SetID("TestUseActionScene");

	SceneManager::GetInstance()->m_scene_object_used_cb = ObjectUsedTest;

	UseAction use_action;
	ExecuteResults results;
	EXPECT_FALSE(use_action.IsValidPayload(&scene_object));
	scene_object.AddUseComponent();
	scene_object.GetUseComponent()->SetUsable(false);
	EXPECT_FALSE(use_action.IsValidPayload(&scene_object));
	scene_object.GetUseComponent()->SetUsable(true);
	scene_object.SetIsValid(false);
	EXPECT_FALSE(use_action.IsValidPayload(&scene_object));
	scene_object.SetIsValid(true);
	EXPECT_FALSE(use_action.IsValidPayload(nullptr));

	use_action.Execute(&scene_object, results);
	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(results.m_result_string == "success");

	scene_object.GetUseComponent()->SetDestroyOnUse(true);
	use_action.Execute(&scene_object, results);
	EXPECT_TRUE(results.m_success);
	EXPECT_TRUE(results.m_result_string == "success");
	EXPECT_FALSE(scene_object.GetIsValid());

	SceneManager::GetInstance()->m_scene_object_used_cb = nullptr;
}
