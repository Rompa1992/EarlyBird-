#include "actors/Ball_Regular.h"

#include "utilities/Math.h"

namespace bo
{
	Ball_Regular::Ball_Regular(World* owningWorld, float circleRadius, sf::Color color)
		: Ball_Base{ owningWorld, circleRadius, color },
		_hasHitActor{ false }
	{
		_velocity = { 20.f , 300.f }; // random range X
	}

	void Ball_Regular::Tick(float deltaTime)
	{
		AddActorLocationOffset(_velocity * deltaTime);

		float accumulatedTime =+ deltaTime;
		float threeFrames = 3 * deltaTime;

		if (accumulatedTime >= threeFrames)
		{
			if (_hasHitActor)
				_hasHitActor = true;
			else
				_hasHitActor = false;
		}
	}

	void Ball_Regular::BeginPlay()
	{
		Ball_Base::BeginPlay();

		//@Note: SetEnablePhysics(true); called from actor BeginPlay();
	}

	void Ball_Regular::OnActorBeginOverlap(Actor* hitActor)
	{
		PRINT_COLOR(BLUE, "Actor Overlapped");

		if (!_hasHitActor)
		{
			if (_velocity.y < 0)
				_velocity.y = 0 + _velocity.y * -1.f;
			else if (_velocity.y > 0)
				_velocity.y = 0 + (_velocity.y * -1.f);

		}
	}

	void Ball_Regular::OnActorEndOverlap(Actor* hitActor)
	{
	}

}



