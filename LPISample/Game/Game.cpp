#include "Game.h"
#include <iostream>
#include "Actions/LookAction.h"
#include "Objects/SceneObject.h"
#include "Lexer/Lexer.h"
#include "Util/LPIUtil.h"
#include "Scene/SceneManager.h"

void Game::Init()
{
	// initialize scene manager with first scene
	SceneManager::GetInstance()->SetCurrentScene(&m_main_scene);

	// setup available actions
	m_actions.push_back(new LookAction());
	
	// setup scene objects
	SceneObject* some_object = new SceneObject();
	some_object->SetID("1");
	some_object->SetDescription("A regular looking llama.\n");
	some_object->AddNoun("LLAMA");

	// setup scene
	m_main_scene.AddSceneObject(some_object);
	m_main_scene.SetSceneDescription(
		"You stand in a grass field that stretches to the horizon in every direction.\n"
		"A llama is nearby.\n"
	);
	// parse grammar 
	const bool parsed_grammar = m_grammar.ParseFile("data/test/grammar.bnf");
	if (!parsed_grammar)
	{
		std::cout << "FAILED!" << std::endl;
	}
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

		SceneObject* found_object = m_main_scene.FindByNoun(noun);

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
			}
		}
	}
}
