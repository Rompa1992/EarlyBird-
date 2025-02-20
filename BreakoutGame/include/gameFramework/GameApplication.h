#pragma once

#include "framework/Application.h"								// must include as we are not just using a pointer to the Application in the header, we are inhereting from it. 
#include "utilities/Core.h"

namespace eb
{
	class Actor;
	class World;
}

namespace bo
{
	class GameApplication : public eb::Application
	{

	public:
		GameApplication();

		void AdvanceToNextLevel();

		void SetCurrentLevel(int newLevel) { _currentLevel = newLevel; }

	private:
		void LoadCurrentLevel();

		int _currentLevel;

		eb::weak_ptr<eb::World> _currentWorld;

	};
}