#include "gameFramework/GameApplication.h"

#include "levels/LevelOne.h"

eb::Application* GetApplication()
{
	return new bo::GameApplication{};
}

namespace bo
{
	GameApplication::GameApplication()
		: Application(1920, 1080, "Breakout!!!", sf::Style::Resize | sf::Style::Close)
	{
		weak_ptr<LevelOne> newWorld = LoadWorld<LevelOne>();
	}

}