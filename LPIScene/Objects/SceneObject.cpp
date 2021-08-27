#include "SceneObject.h"

const std::string& SceneObject::GetID() const
{
	return m_id;
}

void SceneObject::SetID(const std::string& id)
{
	m_id = id;
}

bool SceneObject::operator==(const std::string& rhs) const
{
	return m_id == rhs;
}

bool SceneObject::operator==(const SceneObject& rhs) const
{
	return m_id == rhs.m_id;
}

bool SceneObject::MatchesNoun(const std::string& noun)
{
	return std::find(m_nouns.begin(), m_nouns.end(), noun) == m_nouns.end();
}

bool SceneObject::MatchesAdjective(const std::string& adjective)
{
	return std::find(m_adjectives.begin(), m_adjectives.end(), adjective) == m_adjectives.end();
}

bool SceneObject::MatchesAdjectiveNoun(const std::string& adjective, const std::string& noun)
{
	return MatchesAdjective(adjective) && MatchesNoun(noun);
}

void SceneObject::AddNoun(const std::string& noun)
{
	m_nouns.push_back(noun);
}

void SceneObject::AddAdjective(const std::string& adjective)
{
	m_adjectives.push_back(adjective);
}

const std::string& SceneObject::GetDescription() const
{
	return m_description;
}

void SceneObject::SetDescription(const std::string& description)
{
	m_description = description;
}