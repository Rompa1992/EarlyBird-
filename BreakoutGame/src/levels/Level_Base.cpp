#include "levels/Level_Base.h"

#include "actors/Ball_Regular.h"
#include "actors/Block_Boundry.h"
#include "actors/Player.h"
#include "gameFramework/GameApplication.h"


///  TODO: documentation of level process. 


namespace bo
{
	Level_Base::Level_Base(eb::Application* owningApplication)
		: World{owningApplication},
		_numberOfLevelBlocksRemaining{},
		_shouldLoadNextLevel{ false }
	{
		_gameApplication = static_cast<GameApplication*>(owningApplication);
	}

	void Level_Base::SpawnBoundryBlocks(eb::World* currentWorld)
	{
		float windowWidth = currentWorld->GetWindowSize().x;
		float windowHeight = currentWorld->GetWindowSize().y;
		float blockThickness{ 500.f };

		// Left
		eb::weak_ptr<Block_Boundry> leftBoundryBlock = currentWorld->SpawnActor<Block_Boundry>(currentWorld, sf::Color::Transparent, sf::Vector2f{ blockThickness, windowHeight });
		leftBoundryBlock.lock()->SetActorLocation(sf::Vector2f{ -blockThickness, 0.f });

		// Top
		eb::weak_ptr<Block_Boundry> topBoundryBlock = currentWorld->SpawnActor<Block_Boundry>(currentWorld, sf::Color::Transparent, sf::Vector2f{ windowWidth, blockThickness });
		topBoundryBlock.lock()->SetActorLocation(sf::Vector2f{ 0.f, -blockThickness });

		// Right
		eb::weak_ptr<Block_Boundry> rightBoundryBlock = currentWorld->SpawnActor<Block_Boundry>(currentWorld, sf::Color::Transparent, sf::Vector2f{ blockThickness, windowHeight });
		rightBoundryBlock.lock()->SetActorLocation(sf::Vector2f{ windowWidth, 0.f });
	}

	void Level_Base::SubtractLevelBlocks()
	{
		--_numberOfLevelBlocksRemaining;

		if (_numberOfLevelBlocksRemaining <= 0)
		{
			DestroyAllActors();
		}
	}

	void Level_Base::SpawnLevelBlocks(eb::World* currentWorld)
	{
		
	}
	void Level_Base::SpawnPlayer(eb::World* currentWorld)
	{
		_player.reset();

		_player = SpawnActor<Player>(currentWorld);
		float playerXStartingPos = GetWindowSize().x / 2 - _player.lock()->GetActorGlobalRectBounds().width / 2;
		float playerYStartingPos = GetWindowSize().y * 0.9;
		_player.lock()->SetActorLocation(sf::Vector2f(playerXStartingPos, playerYStartingPos));
	}
	void Level_Base::SpawnBall(eb::World* currentWorld)
	{
		_ballRegular.reset();

		_ballRegular = SpawnActor<Ball_Regular>(currentWorld);
		float ballXStartingPos = GetWindowSize().x / 2 - _ballRegular.lock()->GetActorGlobalRectBounds().width / 2;
		float ballYStartingPos = GetWindowSize().y * 0.85;
		_ballRegular.lock()->SetActorLocation(sf::Vector2f(ballXStartingPos, ballYStartingPos));
	}
	void Level_Base::Tick(float deltaTime)
	{
		if (GetIsWorldEmptyOfActors())
		{
			_gameApplication->AdvanceToNextLevel();
		}
	}
}