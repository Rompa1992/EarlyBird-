#pragma once 


#include "framework/Object.h"
#include "SFML/Graphics.hpp"
#include "utilities/Core.h"

namespace eb
{
	class Actor;
	class Application;

	/*
	 * The World class acts as a central hub for the game environment. It is responsible for:
	 * - Managing and updating all active actors.
	 * - Spawning and handling the lifecycle of actors.
	 * - Rendering actors to the screen.
	 * - Communicating with the Application class for window size retrieval and game loop execution.
	 * - BASE class for levels
	 *
	 * The World starts with an initialization phase (`BeginPlayInternal`), where it triggers
	 * actors' startup logic and initializes game stages. Each game loop iteration, it updates
	 * active actors (`TickInternal`), renders them (`Render`), and cleans up actors marked for
	 * deletion (`CleanCycle`). Stages are progressed automatically based on game logic.
	 */

	class World : public Object
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();																				// Called from Application template LoadWorld();
		void TickInternal(float deltaTime);																		// Called from Application TickInternal();
		void Render(sf::RenderWindow& window);
		void CleanCycle();

		sf::Vector2u GetWindowSize() const;

		/*
		 * This function creates a new actor, passing a reference to this world
		 * along with any additional arguments required by the actor's constructor.
		 * The new actor is added to the pending actors list for further processing.
		 */
		template<typename ActorType, typename... Args>
		weak_ptr<ActorType> SpawnActor(Args... args);

		~World();

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		/*
		 * Used to get window size.
		 * This will can be used by the actor to check boundries etc.
		*/
		Application* _owningApplication;	
		bool _hasBeganPlay;

		List<shared_ptr<Actor>> _actors;
		List<shared_ptr<Actor>> _pendingActors;

	};

	template<typename ActorType, typename... Args>
	weak_ptr<ActorType> SpawnActor(Args... args)
	{
		shared_ptr<ActorType> spawningActor{ new ActorType(this, args...) };
		_pendingActors.push_back(spawningActor);
		return spawningActor;
	}

}