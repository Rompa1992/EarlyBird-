#include "actors/Ball_Regular.h"

#include "framework/World.h" 
#include "utilities/Math.h"

namespace bo
{
	Ball_Regular::Ball_Regular(World* owningWorld, float circleRadius, sf::Color color)
		: Ball_Base{ owningWorld, circleRadius, color }
	{
		_velocity = { 20.f , 500.f }; /// TODO: random range X
	}

	void Ball_Regular::Tick(float deltaTime)
	{
		AddActorLocationOffset(_velocity * deltaTime);
	}

	void Ball_Regular::BeginPlay()
	{
		Ball_Base::BeginPlay();
		SetPhysicsEnabled(true);
	}

	void Ball_Regular::OnActorBeginOverlap(Actor* hitActor)
	{
		/* CollisionResponseCases:
		 * 
		 *  normal = GetBallHitNormal();
		 * 
		 *  Vertical Collision:
		 *    A. Ball Moving UP & TOP HIT || DOWN & BOTTOM HIT
		 *		 if ( normal.y == -1 || normal.y == 1)
		 *			_velocity.y *= -1;
		 *
		 *  Horizontal Collision - static block:
		 *    C. Ball LEFT || RIGHT Side Hit & Ball Moving DOWN || UP
		 *		 if ( normal.x == -1 || normal.x == 1)
		 *			_velocity.x *= -1;
		 * 
		 *  Horizontal Collisions - with player moving:
		 *    C. Ball Left Side Hit - Ball Moving DOWN & Player Moving LEFT
		 *       - x *= -1
		 *       - Adjust downward velocity
		 *    D. Ball Right Side Hit - Ball Moving DOWN & Player Moving RIGHT
		 *       - x *= -1
		 *       - Adjust downward velocity
		 * 
		 *       - Adjust downward velocity
		 *
		 *  Edge Case Considerations:
		 *     - Handling velocity zero-crossing
		 *     - Preventing velocity anomalies
		 *     - Detailed movement interaction
		 *
		*/
		sf::Vector2f normal = GetBallHitNormal(_velocity, hitActor->GetActorGlobalRectBounds(), GetActorGlobalRectBounds());

		// Get Player Velocity ===================================
		float playerVelocity{0.f};
		float playerImpartSpeed{ 75.f };

		if(Player* playerPtr = dynamic_cast<Player*>(hitActor))
			 playerVelocity = playerPtr->GetVelocity();
		// End Get Player Velocity ===============================

		/// TODO: implement all cases for the following, and comments.
		
		if (std::abs(playerVelocity) > 0.f) // Player imparts speed upon the ball
		{
			if (normal.y == -1 || normal.y == 1)
			{
				_velocity.y *= -1;

				if (playerVelocity < 0.f)
					_velocity.x -= playerImpartSpeed;
				else
					_velocity.x += playerImpartSpeed;
			}
			else if (normal.x == -1 || normal.x == 1)
				_velocity.x *= -1;
		}
		else // ball hits a static block
		{

			if (normal.y == -1 || normal.y == 1)
				_velocity.y *= -1;
			else if (normal.x == -1 || normal.x == 1)
				_velocity.x *= -1;
		}

		
		PRINT_COLOR(CYAN, "Vector: %f, %f", normal.x, normal.y);
		PRINT_COLOR(RED, "Player vel: %f", playerVelocity);
	}

	void Ball_Regular::OnActorEndOverlap(Actor* hitActor)
	{
	}

	sf::Vector2f Ball_Regular::GetBallHitNormal(const sf::Vector2f ballVelocity, const sf::FloatRect& blockBounds, const sf::FloatRect& ballBounds) 
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

		
		const int frameRate = GetWorld()->GetTargetFrameRate();
		float intersectionCompensation{ (std::abs(_velocity.y) / frameRate) * 2.f }; // Adjust for actor position inaccuracies caused by ball penetrating block during collision detection

		if (ballVelocity.y < 0.f) // Ball moving down
		{
			if ((ballBounds.left + ballBounds.width) - intersectionCompensation > blockBounds.left && ballBounds.left + intersectionCompensation < blockBounds.left + blockBounds.width)
			{
				// Ball inside bounds of Block Actor = Bottom of Ball Hit 
				return sf::Vector2f{ 0.f, 1.f }; 
			}
			else if ((ballBounds.left + ballBounds.width) - intersectionCompensation <= blockBounds.left)
			{
				// Ball outside of Block bound on the left = Left Side of ball Hit 
				return sf::Vector2f{ -1.f, 0.f };
			}
			else if (ballBounds.left + intersectionCompensation >= blockBounds.left + blockBounds.width)
			{
				// Ball outside of Block bound on the right = Right Side of ball Hit
				return sf::Vector2f{ 1.f, 0.f };
			}
			else
			{
				PRINT_COLOR(RED, "GetSurfaceNormal: Ball moving down. RETURN 0,0");
				return sf::Vector2f{ 0.f, 0.f };
			}
		}
		else if (ballVelocity.y > 0.f) // Ball moving up
		{
			if ((ballBounds.left + ballBounds.width) - intersectionCompensation > blockBounds.left && ballBounds.left + intersectionCompensation < blockBounds.left + blockBounds.width)
			{
				// Ball inside left & right bounds of Block Actor = Top Hit
				return sf::Vector2f{ 0.f, -1.f }; 
			}
			else if ((ballBounds.left + ballBounds.width) - intersectionCompensation <= blockBounds.left)
			{
				// Ball outside of Block bound on the left = Left Side of ball Hit 
				return sf::Vector2f{ -1.f, 0.f };
			}
			else if (ballBounds.left + intersectionCompensation >= blockBounds.left + blockBounds.width)
			{
				// Ball outside of Block bound on the right = Right Side of ball Hit
				return sf::Vector2f{ 1.f, 0.f }; 
			}
			else
			{
				PRINT_COLOR(RED, "GetSurfaceNormal: Ball moving down. RETURN 0,0");
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



