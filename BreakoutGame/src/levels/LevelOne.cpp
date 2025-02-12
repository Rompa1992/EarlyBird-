#include "levels/LevelOne.h"

#include "actors/Ball_Regular.h"
#include "actors/Block_Regular.h"
#include "actors/Player.h"

namespace bo
{
	LevelOne::LevelOne(Application* owningApplication)
		: World{owningApplication}
	{
		_player = SpawnActor<Player>(sf::Vector2f{ 100.f, 25.f }, sf::Color::White);
		float playerXStartingPos = GetWindowSize().x / 2 - _player.lock()->GetActorGlobalRectBounds().width / 2;
		float playerYStartingPos = GetWindowSize().y * 0.9;
		_player.lock()->SetActorLocation(sf::Vector2f(playerXStartingPos, playerYStartingPos));

		_ball = SpawnActor<Ball_Regular>(25.f, sf::Color::Blue);
		float ballXStartingPos = GetWindowSize().x / 2 - _ball.lock()->GetActorGlobalRectBounds().width / 2;
		float ballYStartingPos = GetWindowSize().y * 0.5;
		_ball.lock()->SetActorLocation(sf::Vector2f(ballXStartingPos, ballYStartingPos));

		// test blocks
		_blocks = SpawnActor<Block_Regular>(sf::Vector2f{ 100.f, 25.f }, sf::Color::White);
		float playerXStartingPos_test = GetWindowSize().x / 2 - _player.lock()->GetActorGlobalRectBounds().width / 2 - 300;
		float playerYStartingPos_test = GetWindowSize().y * 0.9;
		_blocks.lock()->SetActorLocation(sf::Vector2f(playerXStartingPos_test, playerYStartingPos));

		// array of blocks
		_blocks.lock()->SpawnBlocks(this);

	}

	void LevelOne::BeginPlay()
	{
		PRINT("Level One Begin Play!");
	}
}