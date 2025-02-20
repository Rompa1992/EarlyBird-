#include "gameFramework/GameApplication.h"

#include "levels/Level_Base.h"
#include "levels/LevelOne.h"
#include "levels/LevelTwo.h"
#include "levels/LevelThree.h"

eb::Application* GetApplication()
{
	return new bo::GameApplication{};
}

namespace bo
{
	GameApplication::GameApplication()
		: Application(1920, 1080, "Breakout!!!", sf::Style::Titlebar | sf::Style::Close),
		_currentLevel{ 1 },
		_currentWorld{}
	{
		LoadCurrentLevel();
	}

	void GameApplication::LoadCurrentLevel() /// TODO: create level spawning system, block and colour types. New blocks, ball reset with lives. basic UI to start the game. 
	{

		// Clear the existing world pointer first
		_currentWorld.reset();  

		switch (_currentLevel) {
		case 1:
			_currentWorld = LoadWorld<LevelOne>();
			break;
		case 2:
			 _currentWorld = LoadWorld<LevelTwo>();
			break;
		case 3:
			 _currentWorld = LoadWorld<LevelThree>();
			break;
		default:
			_currentLevel = 1;
			_currentWorld = LoadWorld<LevelOne>();
		}
	}

	void GameApplication::AdvanceToNextLevel() 
	{
	
		++_currentLevel;
		LoadCurrentLevel();
	}

}