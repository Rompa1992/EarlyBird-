#pragma once

#include "framework/Application.h"								// must include as we are not just using a pointer to the Application in the header, we are inhereting from it. 

namespace bo
{
	class GameApplication : public eb::Application
	{

	public:
		GameApplication();
	};
}