#pragma once
#include <string>
#include <vector>

class SceneObject;
/*
	Stores the execution result when executing an action
*/
struct ExecuteResults
{
	// did the action succeed
	bool m_success = false;

	// user facing result string
	std::string m_result_string;

	// print result string on failure
	bool m_show_result_on_failure = false;

	// equal helper to initialize an execute from a use
	void operator=(const struct UseResults& use_results);
};

/*
	Base class for all actions.
*/
class BaseAction
{
public:
	BaseAction() = default;
	// add a verb that will trigger this action
	void AddVerb(const std::string& verb);

	// does tihs action match the passed in verb
	bool MatchesVerb(const std::string& verb) const;

	// does this action support payload as a valid target
	virtual bool IsValidPayload(const SceneObject* payload) const = 0;

	// does this action support thie multi object payload as a target
	virtual bool IsValidPayload(const std::vector<SceneObject*> payload) const = 0;

	// attempt to execute the action on the payloads
	virtual void Execute(std::vector<SceneObject*> payload, ExecuteResults& results) = 0;

	// attempt to execute the action on the payload
	virtual void Execute(SceneObject* payload, ExecuteResults& results) = 0;

	// general error message
	virtual void GetFailedActionMessage(std::string& message) = 0;
private:
	// verbs that will trigger this action
	std::vector<std::string> m_verbs;
};