#pragma once 

#include "framework/World.h"

namespace bo
{
	class Ball_Regular;
	class Block_Boundry;
	class GameApplication;
	class Player;
	class Level_Base : public eb::World
	{
	public:
		Level_Base(eb::Application* owningApplication);

		void SubtractLevelBlocks();

		virtual void SpawnBoundryBlocks(eb::World* currentWorld);
		virtual void SpawnLevelBlocks(eb::World* currentWorld);
		virtual void SpawnPlayer(eb::World* currentWorld);
		virtual void SpawnBall(eb::World* currentWorld);

		virtual void Tick(float deltaTime) override;

		void SetNumberOfLevelBlocks(int numberOfLevelBlocks) { _numberOfLevelBlocksRemaining = numberOfLevelBlocks; }

		eb::weak_ptr<Player> GetPlayer() const { return _player; }

	private:
		GameApplication* _gameApplication;
		eb::weak_ptr<Player> _player;
		eb::weak_ptr<Ball_Regular> _ballRegular;
		eb::weak_ptr<Block_Boundry> _boundry;

		int _numberOfLevelBlocksRemaining;

		bool _shouldLoadNextLevel;
	};

}