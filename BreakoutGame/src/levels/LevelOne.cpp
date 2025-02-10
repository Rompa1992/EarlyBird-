#include "levels/LevelOne.h"

#include "actors/Player.h"

namespace bo
{
	LevelOne::LevelOne(Application* owningApplication)
		: World{owningApplication}
	{
		_player = SpawnActor<Player>(sf::Vector2f{ 400, 100 }, sf::Color::Red);
		_player.lock()->SetActorLocation(sf::Vector2f(300.f, 500.f));
	}

	void LevelOne::BeginPlay()
	{
		PRINT("Level One Begin Play!");
	}
}