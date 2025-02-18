#pragma once 

#include "framework/World.h"

namespace bo
{
	class Ball_Regular;
	class Block_Boundry;
	class Player;
	class Level_Base : public eb::World
	{
	public:
		Level_Base(eb::Application* owningApplication);

		void SpawnBoundryBlocks(eb::World* currentWorld);

		virtual void SpawnLevelBlocks(eb::World* currentWorld);


		eb::weak_ptr<Player> GetPlayer() const { return _player; }

	private:
		eb::weak_ptr<Player> _player;
		eb::weak_ptr<Ball_Regular> _ballRegular;
		eb::weak_ptr<Block_Boundry> _boundry;
	};

}