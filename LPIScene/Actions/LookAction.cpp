#include "LookAction.h"
#include "Objects/SceneObject.h"
#include <cassert>

LookAction::LookAction()
{
	AddVerb("LOOK");
}

void LookAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	results.m_success = false;
	// look action only takes one objects
	if (payload.size() != 1)
	{
		return;
	}

	return Execute(payload[0], results);
	
}

void LookAction::Execute(SceneObject* payload, ExecuteResults& results)
{
	assert(payload != nullptr);
	results.m_success = true;
	results.m_result_string = payload->GetDescription();
}
