#include "Game.h"
#include <iostream>
#include "Actions/LookAction.h"
#include "Actions/WalkAction.h"
#include "Actions/PickupAction.h"
#include "Actions/ListInventoryAction.h"
#include "Objects/SceneObject.h"
#include "Objects/SceneExitObject.h"
#include "Objects/SceneInventoryObject.h"
#include "Lexer/Lexer.h"
#include "Util/LPIUtil.h"
#include "Scene/SceneManager.h"

void Game::Init()
{
	// initialize scene manager with first scene
	SceneManager::GetInstance()->SetCurrentScene(&m_main_scene);

	// setup available actions
	m_actions.push_back(new LookAction());
	m_actions.push_back(new WalkAction());
	m_actions.push_back(new PickupAction());
	m_actions.push_back(new ListInventoryAction());
	
	// setup scene objects
	SceneObject* some_object = new SceneObject();
	some_object->SetID("1");
	some_object->SetDescription("A regular looking llama.\n");
	some_object->AddNoun("LLAMA");

	SceneObject* main_scene_north_exit = new SceneExitObject(&m_north_scene);
	main_scene_north_exit->SetID("2");
	main_scene_north_exit->SetDescription("To the north the grass has a white tint.\n");
	main_scene_north_exit->AddNoun("NORTH");

	SceneObject* north_scene_south_exit = new SceneExitObject(&m_main_scene);
	north_scene_south_exit->SetID("3");
	north_scene_south_exit->SetDescription("You see a llama and greener pastures to the south.\n");
	north_scene_south_exit->AddNoun("SOUTH");

	SceneObject* key_object = new SceneInventoryObject();
	key_object->SetID("4");
	key_object->SetDescription("An old rusty key.\n");
	key_object->SetShortName("a key");
	key_object->AddNoun("KEY");

	// setup scene
	m_main_scene.AddSceneObject(main_scene_north_exit);
	m_main_scene.AddSceneObject(some_object);
	m_main_scene.AddSceneObject(key_object);
	m_main_scene.SetSceneDescription(
		"You stand in a grass field that stretches to the horizon in every direction.\n"
		"A llama is nearby. A key lays on the ground. There is an exit to the north.\n"
	);

	m_north_scene.AddSceneObject(north_scene_south_exit);
	m_north_scene.SetSceneDescription(
		"Lots of snow here. You see a llama and greener pastures to the south.\n"
	);

	// parse grammar 
	const bool parsed_grammar = m_grammar.ParseFile("data/test/grammar.bnf");
	if (!parsed_grammar)
	{
		std::cout << "FAILED!" << std::endl;
	}

	SceneManager::GetInstance()->m_scene_change_cb = std::bind(
		&Game::SceneChangeCallback,
		this,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3
	);
}

const std::vector<class BaseAction*>& Game::GetActions() const
{
	return m_actions;
}

void Game::ProcessCommand(const std::string& command)
{
	Lexer lexer;
	std::vector<BNFMatchResult> match_results;
	lexer.MatchString(command, match_results, m_grammar);

	std::string verb, noun;
	for (const BNFMatchResult& match_result : match_results)
	{
		if (LPIUtil::IsVerb(match_result.m_symbol))
		{
			verb = match_result.m_expression_term.value;
		}
		else if (LPIUtil::IsNoun(match_result.m_symbol))
		{
			noun = match_result.m_expression_term.value;
		}
	}

	if (verb.length() != 0)
	{
		auto found_action = std::find_if(m_actions.begin(), m_actions.end(),
			[&verb](const BaseAction* action)
			{
				return action->MatchesVerb(verb);
			}
		);

		SceneObject* found_object = SceneManager::GetInstance()->GetCurrentScene()->FindByNoun(noun);
		if (found_object == nullptr)
		{
			found_object = SceneManager::GetInstance()->GetCharacterScene()->FindByNoun(noun);
		}
		if (found_action != m_actions.end())
		{
			ExecuteResults execute_results;
			if ((*found_action)->IsValidPayload(found_object))
			{
				(*found_action)->Execute(found_object, execute_results);

				if (execute_results.m_success)
				{
					std::cout << execute_results.m_result_string << std::endl;
				}
				else
				{
					if (execute_results.m_show_result_on_failure)
					{
						std::cout << execute_results.m_result_string << std::endl;
					}
					else
					{
						std::string fail_message;
						(*found_action)->GetFailedActionMessage(fail_message);
						std::cout << fail_message << std::endl;
					}
				}
			}
			else
			{
				std::string fail_message;
				(*found_action)->GetFailedActionMessage(fail_message);
				std::cout << fail_message << std::endl;
			}
		}
	}
}

void Game::SceneChangeCallback(SceneObject* payload, Scene* source, Scene* destination)
{
	if (payload->GetID() == "4" && destination->GetID() == "INVENTORY_SCENE")
	{
		m_main_scene.SetSceneDescription(
			"You stand in a grass field that stretches to the horizon in every direction.\n"
			"A llama is nearby. There is an exit to the north.\n"
		);
	}
}
