#pragma once
#include <string>
#include <vector>

class SceneObject
{
public:
	SceneObject() = default;

	const std::string& GetID() const;
	void SetID(const std::string& id);

	const std::string& GetDescription() const;
	void SetDescription(const std::string& description);

	bool operator==(const std::string& rhs) const;
	bool operator==(const SceneObject& rhs) const;

	bool MatchesNoun(const std::string& noun);
	bool MatchesAdjective(const std::string& adjective);
	bool MatchesAdjectiveNoun(const std::string& adjective, const std::string& noun);
private:
	std::string m_id;
	std::string m_description;
	std::vector<std::string> m_nouns;
	std::vector<std::string> m_adjectives;
};