#include "actors/Block_Regular.h"

#include "framework/World.h"
#include "utilities/Core.h"

namespace bo
{
	// public:
	// =======
	Block_Regular::Block_Regular(eb::World* owningWorld, sf::Vector2f rectSize, sf::Color color)
		: Block_Base{ owningWorld, rectSize, color }
	{
	}

	void Block_Regular::Tick(float deltaTime)
	{
	}

	void Block_Regular::BeginPlay()
	{
		Block_Base::BeginPlay();
		SetPhysicsEnabled(true);
	}

	void Block_Regular::OnActorBeginOverlap(Actor* hitActor)
	{
		Destroy();
	}

	void Block_Regular::OnActorEndOverlap(Actor* hitActor)
	{
	}

	// private:
	// ========
	void Block_Regular::SpawnBlocks(eb::World* currentWorld)
	{
		float blockWidth{ 100.f };
		float blockHeight{ 25.f };

		float blockSpacing{ 25.f };

		float blockStartingXOffset{ 100.f };
		float blockXOffset{ blockWidth + blockSpacing };

		float blockStartingYOffset{ 50.f };
		float blockYOffset{ blockHeight + blockSpacing };

		int rows{ 10 };
		int columns{ 15 };

		sf::Color blockColor{};

		for (int i = 0; i < rows - 1 ; i++)
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

				eb::weak_ptr<Block_Regular> block = currentWorld->SpawnActor<Block_Regular>(sf::Vector2f{ blockWidth, blockHeight }, blockColor);
				block.lock()->SetActorLocation(sf::Vector2f(j * blockXOffset + blockStartingXOffset, i * blockYOffset + blockStartingYOffset));
			}
		}
	}
}
