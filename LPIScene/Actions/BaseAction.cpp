#include "BaseAction.h"

void BaseAction::AddVerb(const std::string& verb)
{
	m_verbs.push_back(verb);
}

bool BaseAction::MatchesVerb(const std::string& verb) const
{
	return std::find(m_verbs.begin(), m_verbs.end(), verb) != m_verbs.end();
}
