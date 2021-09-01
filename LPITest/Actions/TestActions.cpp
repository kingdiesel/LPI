#include "pch.h"
#include <gtest/gtest.h>
#include "Actions/BaseAction.cpp"
#include "Actions/LookAction.cpp"

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