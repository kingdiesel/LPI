#include "pch.h"
#include <gtest/gtest.h>
#include "Scene/Scene.h"
#include "Objects/SceneObject.cpp"

TEST(TestObjects, TestID)
{
	SceneObject scene_object;
	scene_object.SetID("one");
	EXPECT_TRUE(scene_object.GetID() == "one");
}

TEST(TestObjects, TestDescription)
{
	SceneObject scene_object;
	scene_object.SetID("one");
	scene_object.SetDescription("a thing");
	EXPECT_TRUE(scene_object.GetDescription() == "a thing");
}

TEST(TestObjects, TestValid)
{
	SceneObject scene_object;
	EXPECT_TRUE(scene_object.GetIsValid());
	scene_object.SetIsValid(false);
	EXPECT_FALSE(scene_object.GetIsValid());
}

TEST(TestObjects, TestMatching)
{
	SceneObject scene_object;
	scene_object.SetID("one");
	scene_object.SetDescription("a thing");
	scene_object.AddNoun("FROG");
	scene_object.AddAdjective("BLUE");
	EXPECT_TRUE(scene_object.MatchesAdjective("BLUE"));
	EXPECT_TRUE(scene_object.MatchesNoun("FROG"));
	EXPECT_TRUE(scene_object.MatchesAdjectiveNoun("BLUE", "FROG"));
	EXPECT_FALSE(scene_object.MatchesAdjective("GREEN"));
	EXPECT_FALSE(scene_object.MatchesNoun("LLAMA"));
	EXPECT_FALSE(scene_object.MatchesAdjectiveNoun("BLUE", "LLAMA"));
	EXPECT_FALSE(scene_object.MatchesAdjectiveNoun("GREEN", "FROG"));
}
