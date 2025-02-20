#include "levels/LevelThree.h"

#include "actors/Block_Regular.h"
#include "actors/Player.h"

namespace bo
{
	LevelThree::LevelThree(Application* owningApplication)
		: Level_Base{ owningApplication }
	{
		SpawnBoundryBlocks(this);
		SpawnLevelBlocks(this);
		SpawnPlayer(this);
		SpawnBall(this);
	}

	void LevelThree::SpawnBoundryBlocks(eb::World* currentWorld)
	{
		Level_Base::SpawnBoundryBlocks(currentWorld);
	}

	void LevelThree::SpawnLevelBlocks(eb::World* currentWorld)
	{
		float blockSpacing{ 25.f };

		float blockStartingXOffset{ 100.f };
		float blockStartingYOffset{ 50.f };

		int rows{ 10 }; // Default 10, should be static constexpr?
		int columns{ 15 }; // Default 15, should be static constexpr?

		int numberOfLevelBlocks{};

		sf::Color blockColor{};

		for (int i = 0; i < rows - 1; i++)
		{
			for (int j = 0; j < columns - 1; j++)
			{
				switch (j % 5)
				{
				case 0: blockColor = sf::Color::Red; break;
				case 1: blockColor = sf::Color::Green; break;
				case 2: blockColor = sf::Color::Blue; break;
				case 3: blockColor = sf::Color::Yellow; break;
				case 4: blockColor = sf::Color::Magenta; break;
				default: blockColor = sf::Color::White; break;
				}

				eb::weak_ptr<Block_Regular> block = currentWorld->SpawnActor<Block_Regular>(currentWorld, blockColor);
				block.lock()->SetActorLocation(sf::Vector2f(j * (block.lock()->GetActorGlobalRectBounds().width + blockSpacing) + blockStartingXOffset, i * (block.lock()->GetActorGlobalRectBounds().height + blockSpacing) + blockStartingYOffset));

				++numberOfLevelBlocks;
			}
		}

		SetNumberOfLevelBlocks(numberOfLevelBlocks);
	}

	void LevelThree::SpawnPlayer(eb::World* currentWorld)
	{
		Level_Base::SpawnPlayer(currentWorld);
	}

	void LevelThree::SpawnBall(eb::World* currentWorld)
	{
		Level_Base::SpawnBall(currentWorld);
	}

	void LevelThree::BeginPlay()
	{
		PRINT("Level Three Begin Play!");
	}
}
