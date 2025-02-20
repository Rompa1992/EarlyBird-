#include "actors/Ball_Regular.h"

#include "utilities/Core.h"
#include "utilities/Math.h"

namespace bo
{
	Ball_Regular::Ball_Regular(World* owningWorld, sf::Color color, float radiusSize)
		: Ball_Base{ owningWorld, color, radiusSize }
	{
		SetVelocity(sf::Vector2f{ RandomRange(-80.f, 80.f) , -600.f }); /// TODO: random range X
	}

	void Ball_Regular::Tick(float deltaTime)
	{
		Ball_Base::Tick(deltaTime);
		AddActorLocationOffset(_velocity * deltaTime);
	}

	void Ball_Regular::BeginPlay()
	{
		Ball_Base::BeginPlay();
		SetPhysicsEnabled(true);
	}

	void Ball_Regular::OnActorBeginOverlap(Actor* hitActor)
	{
		Ball_Base::OnActorBeginOverlap(hitActor);

		/* CollisionResponseCases:
		 * 
		 *  normal = GetBallHitNormal();
		 * 
		 *  Vertical Collision - Player Moving:
		 *    A. Ball Moving UP & TOP HIT || DOWN & BOTTOM HIT
		 *		 if ( normal.y == -1 || normal.y == 1)
		 *			_velocity.y *= -1;
		 *			player Imparts friction speed based on player velocity
		 *
		 *  Horizontal Collisions - Player moving:
		 *    B. Ball Side Hit - Ball Moving DOWN & Ball Moving L || R
		 *									   && Player Moving L || R
		 *		 if ( normal.x == -1 || normal.x == 1)
		 *			 x *= -1
		 *			 player side hit speed based on player velocity
		 * 
		 *	  C. Ball Side Hit - Ball Moving DOWN & Ball Moving L || R
		 *									   && Player Moving R || L 
		 *		 if ( normal.x == -1 || normal.x == 1)
		 *			 x *= 1 
		 *			 player side hit speed based on player velocity
		 *
		 * 	Vertical Collision - Static Block:
		 *    D. Ball Moving UP & TOP HIT || DOWN & BOTTOM HIT
		 *		 if ( normal.y == -1 || normal.y == 1)
		 *			_velocity.y *= -1;
		 * 
		 *  Horizontal Collision - Static block:
		 *    E. Ball LEFT || RIGHT Side Hit & Ball Moving DOWN || UP
		 *		 if ( normal.x == -1 || normal.x == 1)
		 *			_velocity.x *= -1;
		 * 
		 *
		*/

		sf::Vector2f normal = GetBallHitNormal(_velocity, hitActor->GetActorGlobalRectBounds(), GetActorGlobalRectBounds());

		// Get Player Velocity ===================================
		float playerVelocity{};

		if(Player* playerPtr = dynamic_cast<Player*>(hitActor))
			 playerVelocity = playerPtr->GetVelocity();
		// End Get Player Velocity ===============================

		/// TODO: implement all cases for the following, and comments.
		
		if (std::abs(playerVelocity) > 0.f) // Player imparts speed upon the ball
		{
			if (normal.y == -1.f || normal.y == 1.f)
			{
				// Case A
				_velocity.y *= -1.f;

				if (playerVelocity < 0.f)
					_velocity.x -= PlayerImpartFrictionSpeed;
				else
					_velocity.x += PlayerImpartFrictionSpeed;
			}
		else if (normal.x == -1.f || normal.x == 1.f)
			{
				// Case B
				if (playerVelocity < 0.f && _velocity.x < 0.f)
				{
					 // B.L && P.L (++)
					_velocity.x -= PlayerImpartSideHitSpeed;
				}
				else if (playerVelocity > 0.f && _velocity.x > 0.f)
				{
					// B.R && P.R (++)
					_velocity.x += PlayerImpartSideHitSpeed;
				}
				else if (playerVelocity > 0.f && _velocity.x < 0.f)
				{
					// B.L && P.R (++)
					_velocity.x = _velocity.x * -1.f + PlayerImpartSideHitSpeed;
				}
				else if (playerVelocity < 0.f && _velocity.x > 0.f)
				{
					// B.R && P.L (++)
					_velocity.x = _velocity.x * -1.f - PlayerImpartSideHitSpeed;
				}
			}	
		}
		else // ball hits a static block
		{

			if (normal.y == -1.f || normal.y == 1.f)
				_velocity.y *= -1.f;
			else if (normal.x == -1.f || normal.x == 1.f)
				_velocity.x *= -1.f;
		}

		// PRINT_COLOR(CYAN, "Vector: %f, %f", normal.x, normal.y);
		// PRINT_COLOR(RED, "Player vel: %f", playerVelocity);
	}

	void Ball_Regular::OnActorEndOverlap(Actor* hitActor)
	{
		Ball_Base::OnActorEndOverlap(hitActor);
	}
}



