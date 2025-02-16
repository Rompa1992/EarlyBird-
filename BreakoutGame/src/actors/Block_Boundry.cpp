#include "actors/Block_Boundry.h"

#include "utilities/Core.h"
#include "framework/World.h"

namespace bo
{
	Block_Boundry::Block_Boundry(eb::World* owningWorld, sf::Vector2f rectSize, sf::Color color)
		: Block_Base{owningWorld, rectSize, color }
	{
	}

	void Block_Boundry::Tick(float deltaTime)
	{
	}

	void Block_Boundry::BeginPlay()
	{
		Block_Base::BeginPlay();
		SetPhysicsEnabled(true);
	}

	void Block_Boundry::SpawnBoundry(eb::World* currentWorld)
	{
		float windowWidth = currentWorld->GetWindowSize().x;
		float windowHeight = currentWorld->GetWindowSize().y;
		float blockThickness{ 500.f };

		// Left
		eb::weak_ptr<Block_Boundry> leftBoundryBlock = currentWorld->SpawnActor<Block_Boundry>(sf::Vector2f{ blockThickness, windowHeight });
		leftBoundryBlock.lock()->SetActorLocation(sf::Vector2f{ -blockThickness, 0.f });

		// Top
		eb::weak_ptr<Block_Boundry> topBoundryBlock = currentWorld->SpawnActor<Block_Boundry>(sf::Vector2f{ windowWidth, blockThickness });
		topBoundryBlock.lock()->SetActorLocation(sf::Vector2f{ 0.f, -blockThickness });

		// Right
		eb::weak_ptr<Block_Boundry> rightBoundryBlock = currentWorld->SpawnActor<Block_Boundry>(sf::Vector2f{ blockThickness, windowHeight });
		rightBoundryBlock.lock()->SetActorLocation(sf::Vector2f{ windowWidth, 0.f });
	}

}