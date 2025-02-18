#pragma once 

#include "levels/Level_Base.h"


namespace bo
{
	class Block_Regular;
	class LevelOne : public Level_Base
	{
	public:
		LevelOne(eb::Application* owningApplication);

		virtual void SpawnLevelBlocks(eb::World* currentWorld) override;
	
	private:
		virtual void BeginPlay() override;

		eb::weak_ptr<Block_Regular> _blocks;
	};
}