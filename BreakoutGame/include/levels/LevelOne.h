#pragma once 

#include "framework/World.h"

using namespace eb;

namespace bo
{
	class Block_Regular;
	class Player;
	class LevelOne : public World
	{
	public:
		LevelOne(Application* owningApplication);
	
	private:
		virtual void BeginPlay() override;
		 
		weak_ptr<Player> _player;
		weak_ptr<Block_Regular> _blocks;
	};
}