#include "actors/Player.h"

#include "utilities/Core.h"

namespace bo
{
	// public:
	// =======
	Player::Player(eb::World* owningWorld, sf::Vector2f rectSize, sf::Color color)
		: Block_Base{ owningWorld, rectSize, color },
		_moveInput{ 0.f },
		_speed{ 500.f },
		_velocity{ 0.f }
	{

	}

	void Player::Tick(float deltaTime)
	{
		Block_Base::Tick(deltaTime);
		AddActorLocationOffset(sf::Vector2f{ GetVelocity(), 0.f } * deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void Player::BeginPlay()
	{
		Block_Base::BeginPlay();
	}

	// private:
	// ========
	void Player::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_moveInput = 1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_moveInput = -1.f;

		ClampInputEdge();
	}

	void Player::ClampInputEdge()
	{
		float playerLocationX = GetActorLocation().x;

		// left side 
		if (playerLocationX < 0 && _moveInput == -1)
			_moveInput = 0.f;

		// right side 
		if (playerLocationX > GetWindowSize().x && _moveInput == 1)
			_moveInput = 0.f;
	}

	void Player::ConsumeInput(float deltaTime)
	{
		SetVelocity(_moveInput * _speed);
		_moveInput = 0.f;
	}
	
}