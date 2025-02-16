#include "gameFramework/GameApplication.h"

#include "levels/LevelOne.h"

eb::Application* GetApplication()
{
	return new bo::GameApplication{};
}

namespace bo
{
	GameApplication::GameApplication()
		: Application(1920, 1080, "Breakout!!!", sf::Style::Titlebar | sf::Style::Close)
	{
		eb::weak_ptr<LevelOne> newWorld = LoadWorld<LevelOne>();
	}

}