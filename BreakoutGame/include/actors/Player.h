#pragma once

#include "actors/Block_Base.h"

using namespace eb;

namespace bo
{
	class Player : public Block_Base
	{
	public:
		Player(World* owningWorld, sf::Vector2f rectSize, sf::Color color);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

		void SetVelocity(float newVelocity) { _velocity = newVelocity; }

		float GetVelocity() const { return _velocity; }

	private:
		void HandleInput();
		void ClampInputEdge();
		void ConsumeInput(float deltaTime);

		float _moveInput;
		float _speed;
		float _velocity;
	};
}