#pragma once 

#include "levels/Level_Base.h"


namespace bo
{
	class Block_Regular;
	class LevelTwo : public Level_Base
	{
	public:
		LevelTwo(eb::Application* owningApplication);

		virtual void SpawnBoundryBlocks(eb::World* currentWorld) override;
		virtual void SpawnLevelBlocks(eb::World* currentWorld) override;
		virtual void SpawnPlayer(eb::World* currentWorld) override;
		virtual void SpawnBall(eb::World* currentWorld) override;

	private:
		virtual void BeginPlay() override;

	};
}