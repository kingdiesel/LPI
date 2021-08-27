#include "LookAction.h"
#include "Objects/SceneObject.h"
#include <cassert>

LookAction::LookAction()
{

}

void LookAction::Execute(std::vector<SceneObject*> payload, ExecuteResults& results)
{
	results.m_success = false;
	// look action only takes one objects
	if (payload.size() != 1)
	{
		return;
	}

	SceneObject* object = payload[0];
	assert(object != nullptr);

	results.m_success = true;
	results.m_result_string = object->GetDescription();
}
