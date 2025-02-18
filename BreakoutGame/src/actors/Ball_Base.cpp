#include "actors/Ball_Base.h"

#include "actors/Block_Boundry.h"
#include "framework/World.h"

namespace bo
{
	Ball_Base::Ball_Base(eb::World* owningWorld, sf::Color color, float radiusSize)
		: Actor{ owningWorld, color, radiusSize },
		_velocity{ 10.f, 10.f },
		_hitActorIsBoundry{ false },
		_targetFrameRate{ owningWorld->GetTargetFrameRate() }
	{
	}
	void Ball_Base::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
	}

	void Ball_Base::BeginPlay()
	{
		Actor::BeginPlay();
	}

	void Ball_Base::OnActorBeginOverlap(Actor* hitActor)
	{
		if (dynamic_cast<Block_Boundry*>(hitActor))
			_hitActorIsBoundry = true;
	}

	void Ball_Base::OnActorEndOverlap(Actor* hitActor)
	{
		_hitActorIsBoundry = false;
	}

	sf::Vector2f Ball_Base::GetBallHitNormal(const sf::Vector2f ballVelocity, const sf::FloatRect& blockBounds, const sf::FloatRect& ballBounds)
	{
		/// BallHitNormal Diagram 
		//
		//					 { 0.f, -1.f }
		//						   |
		//						   |			
		//                     |=======|
		//					   |=======|
		//   { -1.f, 0.f } <-- |=======| --> { 1.f, 0.f }
		//					   |=======|
		//                     |=======|
		//						   |
		//						   |
		//					 { 0.f, 1.f }
		//

		float intersectionCompensation{ std::abs(_velocity.y) / _targetFrameRate }; // Adjust for actor position inaccuracies caused by ball penetrating block during collision detection


		if (_hitActorIsBoundry)
		{
			if (ballBounds.top < 1.f)
			{
				// Ball hit top boundry = Top Hit (++)
				return sf::Vector2f{ 0.f, -1.f };
			}
			else if (ballBounds.left < 1.f)
			{
				// Ball hit left boundry = Left Side of Ball Hit (++)
				return sf::Vector2f{ -1.f, 0.f };
			}
			else if (ballBounds.left > 1.f)
			{
				// Ball hit right boundry = Right Side of Ball Hit (++)
				return sf::Vector2f{ 1.f, 0.f };
			}
			else
			{
				PRINT_COLOR(RED, "GetSurfaceNormal: Ball Hit Boundry. RETURN 0,0");
				return sf::Vector2f{ 0.f, 0.f };
			}
		}
		else if (ballVelocity.y > 0.f) // Ball moving down
		{
			if (ballBounds.left + ballBounds.width - intersectionCompensation > blockBounds.left && ballBounds.left + intersectionCompensation < blockBounds.left + blockBounds.width)
			{
				// Ball inside bounds of Block Actor = Bottom of Ball Hit (++)
				return sf::Vector2f{ 0.f, 1.f };
			}
			else if (ballBounds.left + ballBounds.width - intersectionCompensation <= blockBounds.left)
			{
				// Ball outside of Block bound on the left = Left Side of Ball Hit (++)
				return sf::Vector2f{ -1.f, 0.f };
			}
			else if (ballBounds.left + intersectionCompensation >= blockBounds.left + blockBounds.width)
			{
				// Ball outside of Block bound on the right = Right Side of Ball Hit (++)
				return sf::Vector2f{ 1.f, 0.f };
			}
			else
			{
				PRINT_COLOR(RED, "GetSurfaceNormal: Ball moving DOWN. RETURN 0,0");
				return sf::Vector2f{ 0.f, 0.f };
			}
		}
		else if (ballVelocity.y < 0.f) // Ball moving up
		{
			if (ballBounds.left + ballBounds.width > blockBounds.left && ballBounds.left < blockBounds.left + blockBounds.width)
			{
				// Ball inside left & right bounds of Block Actor = Top Hit (++)
				return sf::Vector2f{ 0.f, -1.f };
			}
			else if ((ballBounds.left + ballBounds.width) - intersectionCompensation <= blockBounds.left)
			{
				// Ball outside of Block bound on the left = Left Side of Ball Hit (++)
				return sf::Vector2f{ -1.f, 0.f };
			}
			else if (ballBounds.left + intersectionCompensation >= blockBounds.left + blockBounds.width)
			{
				// Ball outside of Block bound on the right = Right Side of Ball Hit (++)
				return sf::Vector2f{ 1.f, 0.f };
			}
			else
			{
				PRINT_COLOR(RED, "GetSurfaceNormal: Ball moving UP. RETURN 0,0");
				return sf::Vector2f{ 0.f, 0.f };
			}
		}
		else
		{
			PRINT_COLOR(RED, "GetSurfaceNormal: Ball NO DIRECTION. RETURN 0,0");
			return sf::Vector2f{ 0.f, 0.f };
		}
	}
}