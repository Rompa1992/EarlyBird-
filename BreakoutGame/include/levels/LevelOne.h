#pragma once 

#include "framework/World.h"

using namespace eb;

namespace bo
{
	class Ball_Regular;
	class Block_Regular;
	class Player;
	class LevelOne : public World
	{
	public:
		LevelOne(Application* owningApplication);
	
	private:
		virtual void BeginPlay() override;
		 
		weak_ptr<Player> _player;
		weak_ptr<Ball_Regular> _ball;
		weak_ptr<Block_Regular> _blocks;
	};
}