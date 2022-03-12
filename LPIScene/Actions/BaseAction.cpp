#include "BaseAction.h"
#include <Scene/SceneManager.h>

void BaseAction::AddVerb(const std::string& verb)
{
	m_verbs.push_back(verb);
}

bool BaseAction::MatchesVerb(const std::string& verb) const
{
	return std::find(m_verbs.begin(), m_verbs.end(), verb) != m_verbs.end();
}

void ExecuteResults::operator=(const UseResults& use_results)
{
	m_result_string = use_results.m_result_string;
	m_success = use_results.m_success;
	m_show_result_on_failure = true;
}
