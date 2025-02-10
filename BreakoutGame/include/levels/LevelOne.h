#pragma once 

#include "framework/World.h"

using namespace eb;

namespace bo
{
	class Player;
	class LevelOne : public World
	{
	public:
		LevelOne(Application* owningApplication);
	
	private:
		virtual void BeginPlay() override;
		 
		weak_ptr<Player> _player;
	};
}