#pragma once 

#include "framework/World.h"


namespace bo
{
	class Ball_Regular;
	class Block_Regular;
	class Block_Boundry;
	class Player;
	class LevelOne : public eb::World
	{
	public:
		LevelOne(eb::Application* owningApplication);
	
	private:
		virtual void BeginPlay() override;
		 
		eb::weak_ptr<Player> _player;
		eb::weak_ptr<Ball_Regular> _ball;
		eb::weak_ptr<Block_Regular> _blocks;
		eb::weak_ptr<Block_Boundry> _boundry;
	};
}