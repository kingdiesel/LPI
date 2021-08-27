#pragma once
#include <string>
#include <vector>

class SceneObject;

struct ExecuteResults
{
	bool m_success = false;
	std::string m_result_string;
};

class BaseAction
{
public:
	BaseAction() = default;
	void AddVerb(const std::string& verb);
	bool MatchesVerb(const std::string& verb);

	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) = 0;
private:
	std::vector<std::string> m_verbs;
};