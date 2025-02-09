#include "framework/Object.h"
#include "utilities/Core.h"

namespace eb
{
	Object::Object()
		: _isPendingDestroy{ false }
	{

	}

	void Object::Destroy()
	{
		// TODO: Broadcast destroy.
		_isPendingDestroy = true;
	}

	Object::~Object()
	{
		PRINT_COLOR(RED, "Object was destroyed")
	}

	
}