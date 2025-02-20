#include "levels/LevelTwo.h"

#include "actors/Block_Regular.h"
#include "actors/Player.h"

namespace bo
{
	LevelTwo::LevelTwo(Application* owningApplication)
		: Level_Base{ owningApplication }
	{
		SpawnBoundryBlocks(this);
		SpawnLevelBlocks(this);
		SpawnPlayer(this);
		SpawnBall(this);
	}

	void LevelTwo::SpawnBoundryBlocks(eb::World* currentWorld)
	{
		Level_Base::SpawnBoundryBlocks(currentWorld);
	}

	void LevelTwo::SpawnLevelBlocks(eb::World* currentWorld)
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

				eb::weak_ptr<Block_Regular> weakBlock = currentWorld->SpawnActor<Block_Regular>(currentWorld, blockColor);
				if (auto block = weakBlock.lock()) // Get shared_ptr once
				{
					float width = block->GetActorGlobalRectBounds().width;
					float height = block->GetActorGlobalRectBounds().height;

					block->SetActorLocation(sf::Vector2f(
						j * (width + blockSpacing) + blockStartingXOffset,
						i * (height + blockSpacing) + blockStartingYOffset));

					++numberOfLevelBlocks;
				}
			}
		}

		SetNumberOfLevelBlocks(numberOfLevelBlocks);
	}

	void LevelTwo::SpawnPlayer(eb::World* currentWorld)
	{
		Level_Base::SpawnPlayer(currentWorld);
	}

	void LevelTwo::SpawnBall(eb::World* currentWorld)
	{
		Level_Base::SpawnBall(currentWorld);
	}

	void LevelTwo::BeginPlay()
	{
		PRINT("Level Two Begin Play!");
	}
}
