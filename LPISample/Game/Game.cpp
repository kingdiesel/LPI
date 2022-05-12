#include "Game.h"
#include <iostream>
#include "Actions/LookAction.h"
#include "Actions/WalkAction.h"
#include "Actions/PickupAction.h"
#include "Actions/ListInventoryAction.h"
#include "Actions/UseAction.h"
#include "Objects/SceneObject.h"
#include "Components/SceneExitComponent.h"
#include "Components/InventoryItemComponent.h"
#include "Components/UseComponent.h"
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
	m_actions.push_back(new UseAction());
	
	// setup scene objects
	SceneObject* some_object = new SceneObject();
	some_object->SetID("1");
	some_object->SetDescription("A regular looking llama.\n");
	some_object->AddNoun("LLAMA");

	SceneObject* main_scene_north_exit = new SceneObject();
	main_scene_north_exit->AddSceneExitComponent();
	main_scene_north_exit->GetSceneExitComponent()->SetSceneExit(&m_north_scene);
	main_scene_north_exit->SetID("2");
	main_scene_north_exit->SetDescription("To the north the grass has a white tint.\n");
	main_scene_north_exit->AddNoun("NORTH");

	SceneObject* north_scene_south_exit = new SceneObject();
	north_scene_south_exit->AddSceneExitComponent();
	north_scene_south_exit->GetSceneExitComponent()->SetSceneExit(&m_main_scene);
	north_scene_south_exit->SetID("3");
	north_scene_south_exit->SetDescription("You see a llama and greener pastures to the south.\n");
	north_scene_south_exit->AddNoun("SOUTH");

	SceneObject* key_object = new SceneObject();
	key_object->AddInventoryItemComponent();
	key_object->AddUseComponent();
	key_object->GetUseComponent()->SetUsable(false);
	key_object->SetID("4");
	key_object->SetDescription("An old rusty key.\n");
	key_object->SetShortName("a key");
	key_object->AddNoun("KEY");

	SceneObject* tissue_object = new SceneObject();
	tissue_object->AddInventoryItemComponent();
	tissue_object->AddUseComponent();
	tissue_object->GetUseComponent()->SetUsable(true);
	tissue_object->GetUseComponent()->SetDestroyOnUse(true);
	tissue_object->SetID("5");
	tissue_object->SetDescription("A fresh tissue.\n");
	tissue_object->SetShortName("a fresh tissue");
	tissue_object->AddNoun("TISSUE");

	SceneObject* slime_object = new SceneObject();
	slime_object->AddUseComponent();
	slime_object->GetUseComponent()->SetUsable(true);
	slime_object->SetID("6");
	slime_object->SetDescription("A pile of slime.\n");
	slime_object->SetShortName("slime");
	slime_object->AddNoun("SLIME");

	// setup scene
	m_main_scene.AddSceneObject(main_scene_north_exit);
	m_main_scene.AddSceneObject(some_object);
	m_main_scene.AddSceneObject(key_object);
	m_main_scene.AddSceneObject(tissue_object);
	m_main_scene.AddSceneObject(slime_object);
	m_main_scene.SetSceneDescription(
		"You stand in a grass field that stretches to the horizon in every direction.\n"
		"A llama is nearby. A key and a tissue lay on the ground. There is an exit to the north.\n"
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

	SceneManager::GetInstance()->m_scene_object_used_cb = std::bind(
		&Game::ObjectUsedCallback,
		this,
		std::placeholders::_1,
		std::placeholders::_2
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

	// todo need to modify this function to accomodate 
	// <verb> <noun> <preposition> <noun>
	std::string verb;
	std::vector<std::string> nouns;
	for (const BNFMatchResult& match_result : match_results)
	{
		if (LPIUtil::IsVerb(match_result.m_symbol))
		{
			verb = match_result.m_expression_term.value;
		}
		else if (LPIUtil::IsNoun(match_result.m_symbol))
		{
			nouns.push_back(match_result.m_expression_term.value);
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

		std::vector<SceneObject*> payload;
		for (const std::string& noun : nouns)
		{
			SceneObject* found_object = SceneManager::GetInstance()->GetCurrentScene()->FindByNoun(noun);
			if (found_object == nullptr)
			{
				found_object = SceneManager::GetInstance()->GetCharacterScene()->FindByNoun(noun);
			}
			
			if (found_object != nullptr)
			{
				payload.push_back(found_object);
			}
		}
		
		if (found_action != m_actions.end())
		{
			ExecuteResults execute_results;
			if ((*found_action)->IsValidPayload(payload))
			{
				(*found_action)->Execute(payload, execute_results);

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
		payload->GetUseComponent()->SetUsable(true);
		if (!m_picked_up_tissue)
		{
			m_main_scene.SetSceneDescription(
				"You stand in a grass field that stretches to the horizon in every direction.\n"
				"A llama is nearby. A tissue lays on the ground. There is an exit to the north.\n"
			);
		}
		else
		{
			m_main_scene.SetSceneDescription(
				"You stand in a grass field that stretches to the horizon in every direction.\n"
				"A llama is nearby. There is an exit to the north.\n"
			);
		}
		m_picked_up_key = true;
	}
	else if (payload->GetID() == "5" && destination->GetID() == "INVENTORY_SCENE")
	{
		payload->GetUseComponent()->SetUsable(true);
		if (!m_picked_up_key)
		{
			m_main_scene.SetSceneDescription(
				"You stand in a grass field that stretches to the horizon in every direction.\n"
				"A llama is nearby. A key lays on the ground. There is an exit to the north.\n"
			);
		}
		else
		{
			m_main_scene.SetSceneDescription(
				"You stand in a grass field that stretches to the horizon in every direction.\n"
				"A llama is nearby. There is an exit to the north.\n"
			);
		}
		m_picked_up_tissue = true;
	}
}

UseResults Game::ObjectUsedCallback(SceneObject* payload, SceneObject* payload2)
{
	UseResults use_results;
	if (payload->GetID() == "5")
	{
		if (payload2 == nullptr)
		{
			use_results.m_success = true;
			use_results.m_result_string = "You blow your nose and the tissue is destroyed.\n";
		}
		else if (payload2->GetID() == "6")
		{
			use_results.m_success = true;
			use_results.m_result_string = "You wipe up the slime and the tissue is destroyed.\n";
			// TODO: memory leak
			payload2->GetParentScene()->RemoveSceneObject(payload2->GetID());
			payload2->SetIsValid(false);
		}
	}
	else
	{
		use_results.m_success = false;
		use_results.m_result_string = "UH OH\n";
	}
	return use_results;
}
