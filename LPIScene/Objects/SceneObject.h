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

	bool MatchesNoun(const std::string& noun) const;
	bool MatchesAdjective(const std::string& adjective) const;
	bool MatchesAdjectiveNoun(const std::string& adjective, const std::string& noun) const;

	void AddNoun(const std::string& noun);
	void AddAdjective(const std::string& adjective);

	virtual std::string GetDebugName() const;
private:
	std::string m_id;
	std::string m_description;
	std::vector<std::string> m_nouns;
	std::vector<std::string> m_adjectives;
};