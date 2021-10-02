// LPISample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "Scene/Scene.h"
#include "Actions/LookAction.h"
#include "Objects/SceneObject.h"
#include "Util/LPIUtil.h"
#include "Lexer/Lexer.h"
#include "BNF/BNF.h"

int main()
{
	std::vector<BaseAction*> Actions;
	Actions.push_back(new LookAction());
	SceneObject* some_object = new SceneObject();
	some_object->SetID("1");
	some_object->SetDescription("A regular looking llama.");
	some_object->AddNoun("LLAMA");

	Scene main_scene;
	main_scene.AddSceneObject(some_object);

	BNF grammar;
	const bool parsed_grammar = grammar.ParseFile("data/test/grammar.bnf");
	if (!parsed_grammar)
	{
		std::cout << "FAILED!" << std::endl;
	}

	Lexer lexer;
	std::vector<BNFMatchResult> match_results;
	lexer.MatchString("LOOK AT LLAMA", match_results, grammar);


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

	if (verb.length() != 0 && noun.length() != 0)
	{
		auto found_action = std::find_if(Actions.begin(), Actions.end(),
			[&verb](const BaseAction* action)
			{
				return action->MatchesVerb(verb);
			}
		);

		SceneObject* found_object = main_scene.FindByNoun(noun);

		if (found_action != Actions.end() && found_object != nullptr)
		{
			ExecuteResults execute_results;
			(*found_action)->Execute(found_object, execute_results);

			if (execute_results.m_success)
			{
				std::cout << execute_results.m_result_string << std::endl;
			}
		}
	}
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
