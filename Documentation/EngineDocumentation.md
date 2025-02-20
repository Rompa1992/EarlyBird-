# Engine Project Documentation

## Index

### Engine Files
1.1.Application.h
1.2.Application.cpp
1.3.EntryPoint.h
1.4.EntryPoint.cpp
1.5.Core.h
1.6.World.h
1.7.GameApplication.h
1.8.GameApplication.cpp
1.9.Object.h
1.10 Core.h
1.11 Levels

### Processes
2.1.Calling An Actor 

### Physics System
3.1 Physics System Overview

---

# Engine Files

### 1.1. **Application.h**
#### **Purpose**:
Defines the `Application` class, which manages the main game loop and rendering.

#### **Key Components**:
- **Constructors**:
  - `Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& windowTitle, sf::Uint32 windowStyle)`
- **Public Methods**:
  - `void RunMainLoop();` - Runs the primary game loop.
  - `sf::Vector2u GetWindowSize() const;` - Returns the window size.
- **Protected Methods**:
  - `virtual void Tick(float deltaTime);` - Called every frame update.
  - `virtual void Render();` - Handles rendering.
- **Private Methods**:
  - `void TickInternal(float deltaTime);` - Calls `Tick` method.
  - `void RenderInternal();` - Calls `Render` method.

---

### 1.2. **Application.cpp**
#### **Purpose**:
Implements the `Application` class, handling the main loop and rendering logic.

#### **Key Components**:
- **`RunMainLoop`**:
  - Processes window events.
  - Implements a fixed time step update loop.
  - Calls `TickInternal` and `RenderInternal`.
- **`TickInternal` & `RenderInternal`**:
  - Wrap calls to `Tick` and `Render`, ensuring controlled execution.
- **`GetWindowSize`**:
  - Returns the window�s size from SFML�s `RenderWindow`.

---

### 1.3. **EntryPoint.h**
#### **Purpose**:
Declares an external function to retrieve the `Application` instance.

#### **Key Components**:
- `extern eb::Application* GetApplication();` - Entry point to create an `Application` instance.

---

### 1.4. **EntryPoint.cpp**
#### **Purpose**:
Defines the main entry point of the application.

#### **Key Components**:
- Calls `GetApplication()` to create the game instance.
- Calls `RunMainLoop()`.
- Deletes the `Application` instance after execution.

---

### 1.5. **Core.h**
#### **Purpose**:
Defines utility types and macros.

#### **Key Components**:
- **Custom Aliases**:
  - `unique_ptr<T>` - Wrapper for `std::unique_ptr<T>`.
  - `shared_ptr<T>` - Wrapper for `std::shared_ptr<T>`.
  - `weak_ptr<T>` - Wrapper for `std::weak_ptr<T>`.
  - `List<T>` - Wrapper for `std::vector<T>`.
  - `Map<Key, Value>` - Wrapper for `std::map<Key, Value>`.
- **Color Macros**:
  - ANSI color escape codes for console output.
- **Logging Macros**:
  - `PRINT_COLOR(color, log, ...)`
  - `PRINT(log, ...)`

---

### 1.6. **World.h**

#### Purpose:
The World class serves as a foundational environment manager for game worlds/levels. 
It manages the game's actor lifecycle, updates, rendering, and serves as the intermediary between the game application and individual actors.

#### Key Components:

- **Inheritance & Relationships**:
 - Inherits from `Object` for smart pointer management
 - Owned by `Application`
 - Owns and manages collection of `Actor` instances

- **Initialization & Core Loop**:
 - `World(Application* owningApp);`  
   Constructor that establishes ownership relationship with Application.
 - `void BeginPlayInternal();`  
   Internal initialization trigger called once by Application's LoadWorld.
 - `void TickInternal(float deltaTime);`  
   Main update loop handling actor updates and pending actor initialization.
 - `void Render(sf::RenderWindow& window);`  
   Renders all active actors to the provided window.
 - `void CleanCycle();`  
   Safe removal of destroyed actors using iterator-safe pattern.

- **Actor Management**:
 - `template<typename ActorType, typename... Args>`  
   `weak_ptr<ActorType> SpawnActor(Args... args);`  
   Template function for creating new actors with variable constructor arguments.
   Returns weak_ptr to avoid circular references.

- **Private Members & Virtual Functions**:
 - `Application* _owningApplication`  
   Non-owning pointer to parent application for window access.
 - `bool _hasBeganPlay`  
   Flag ensuring BeginPlay only occurs once.
 - `List<shared_ptr<Actor>> _actors`  
   Collection of active actors in the world.
 - `List<shared_ptr<Actor>> _pendingActors`  
   Staging area for newly created actors awaiting initialization.
 - `virtual void BeginPlay();`  
   Override point for world-specific initialization.
 - `virtual void Tick(float deltaTime);`  
   Override point for world-specific updates.

#### Actor Lifecycle Management:
1. **Creation**: Actors spawned via SpawnActor enter _pendingActors
2. **Initialization**: Next tick moves them to _actors and calls BeginPlayInternal
3. **Updates**: Active actors receive TickInternal calls each frame
4. **Destruction**: CleanCycle removes actors marked for destruction
5. **Cleanup**: World destructor handles final cleanup of all actors

---

### 1.7. **GameApplication.h**
#### **Purpose**:
Defines `GameApplication`, which inherits from `Application`.

#### **Key Components**:
- `class GameApplication : public eb::Application` - Custom game-specific application class.
- Constructor: `GameApplication();`

---

### 1.8. **GameApplication.cpp**
#### **Purpose**:
Implements `GameApplication` and provides an instance of it.

#### **Key Components**:
- `GameApplication::GameApplication()`:
  - Initializes the application with resolution `1920x1080`.
  - Enables `Resize` and `Close` window styles.
- `eb::Application* GetApplication()`:
  - Returns a new `GameApplication` instance.

---

### 1.9. **Object.h**
#### **Purpose**:
Defines the `Object` class, a base class for safe object management using smart pointers. It leverages `std::enable_shared_from_this` to allow an object to generate weak references to itself, ensuring proper memory management and avoiding cyclic dependencies.

#### **Key Components**:
- **Inheritance**:
  - Inherits from `std::enable_shared_from_this<Object>`, enabling the use of `weak_from_this()` to safely create `weak_ptr` instances that refer to the current object.
  
- **Constructors & Destructor**:
  - `Object();`  
    Initializes the object.
  - `~Object();`  
    Ensures proper cleanup when the object is destroyed.

- **Public Methods**:
  - `virtual void Destroy();`  
    Marks the object as pending destruction, allowing controlled resource deallocation.
  - `bool IsPendingDestroy() const;`  
    Returns the status of whether the object is scheduled for destruction.
  - `weak_ptr<Object> GetWeakRef();`  
    Returns a non-const weak reference to the object. This version allows subsequent modifications when the weak pointer is locked.
  - `weak_ptr<const Object> GetWeakRef() const;`  
    Returns a const-qualified weak reference, ensuring that the object cannot be modified when accessed through this pointer.

- **Private Members**:
  - `bool _isPendingDestroy;`  
    A flag indicating if the object is pending destruction.

---

### Explanation of the Approach

To integrate the `Object` class documentation into the existing engine project documentation, I structured the section to match the provided style. The new section is numbered appropriately (as section 9) and follows the format used for other components (such as `Application.h` and `GameApplication.h`). Each part of the class is broken down into its purpose and key components, covering inheritance, constructors, public methods, and private members.

### Summary of Steps and Actions Taken

- Analyzed the provided style from the Engine Project Documentation.
- Created a new section titled **Object.h**.
- Documented the class purpose, detailing its role in safe smart pointer management using `std::enable_shared_from_this`.
- Listed key components including inheritance, constructors/destructor, public methods, and private members.
- Ensured the documentation style matches that of the provided examples, focusing solely on the `Object` class.

---
---

## Core.h

### Smart Pointers

#### `unique_ptr<T>`
- **Purpose**: Manages exclusive ownership of a dynamically allocated object.
- **Use Case**: When only one owner should manage the lifetime of the object.
- **Example**:
  ```cpp
  eb::unique_ptr<int> ptr = std::make_unique<int>(42);
  PRINT("Value: %d", *ptr); // Output: Value: 42
  ```
- **Inner Workings**: Automatically deletes the object when the `unique_ptr` goes out of scope. Cannot be copied, but can be moved.

#### `shared_ptr<T>`
- **Purpose**: Manages shared ownership of a dynamically allocated object.
- **Use Case**: When multiple parts of the code need to share ownership of the same object.
- **Example**:
  ```cpp
  eb::shared_ptr<int> ptr1 = std::make_shared<int>(42);
  eb::shared_ptr<int> ptr2 = ptr1; // Both ptr1 and ptr2 share ownership
  PRINT("Value: %d", *ptr2); // Output: Value: 42
  ```
- **Inner Workings**: Uses reference counting to track the number of owners. Deletes the object when the last `shared_ptr` goes out of scope.

#### `weak_ptr<T>`
- **Purpose**: Provides a non-owning reference to an object managed by `shared_ptr`.
- **Use Case**: When you need to observe an object without affecting its lifetime.
- **Example**:
  ```cpp
  eb::shared_ptr<int> shared = std::make_shared<int>(42);
  eb::weak_ptr<int> weak = shared;
  if (auto locked = weak.lock()) {
      PRINT("Value: %d", *locked); // Output: Value: 42
  }
  ```
- **Inner Workings**: Does not increment the reference count. Must be converted to `shared_ptr` to access the object.

---

### Containers

#### `List<T>`
- **Purpose**: A dynamic array that stores elements in a contiguous block of memory.
- **Use Case**: When you need a resizable array with fast random access.
- **Example**:
  ```cpp
  eb::List<int> numbers = {1, 2, 3};
  numbers.push_back(4);
  PRINT("Size: %zu", numbers.size()); // Output: Size: 4
  ```
- **Inner Workings**: Uses a dynamically allocated array that grows as needed. Provides O(1) access by index.

#### `Map<keyType, valueType, predicate>`
- **Purpose**: An associative container that stores key-value pairs in sorted order.
- **Use Case**: When you need to store and retrieve values by a unique key, with keys sorted.
- **Example**:
  ```cpp
  eb::Map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
  ages["Charlie"] = 28;
  PRINT("Bob's age: %d", ages["Bob"]); // Output: Bob's age: 25
  ```
- **Inner Workings**: Implemented as a balanced binary search tree (usually a Red-Black Tree). Provides O(log n) operations.

#### `Set<T>`
- **Purpose**: An unordered collection of unique elements.
- **Use Case**: When you need to store unique elements without caring about their order.
- **Example**:
  ```cpp
  eb::Set<int> numbers = {1, 2, 3};
  numbers.insert(4);
  PRINT("Size: %zu", numbers.size()); // Output: Size: 4
  ```
- **Inner Workings**: Uses a hash table for storage. Provides O(1) average-case operations.

---

### Console Output Macros

#### `PRINT_COLOR(color, log, ...)`
- **Purpose**: Prints a colored message to the console.
- **Use Case**: For debugging or logging with visual distinction.
- **Example**:
  ```cpp
  PRINT_COLOR(RED, "Error: Something went wrong!");
  ```

#### `PRINT(log, ...)`
- **Purpose**: Prints a message to the console.
- **Use Case**: For general logging or debugging.
- **Example**:
  ```cpp
  PRINT("Hello, World!");
  ```

---

### Summary of Use Cases
- **`unique_ptr`**: Use for exclusive ownership.
- **`shared_ptr`**: Use for shared ownership.
- **`weak_ptr`**: Use for non-owning references.
- **`List`**: Use for dynamic arrays.
- **`Map`**: Use for sorted key-value pairs.
- **`Set`**: Use for unordered unique elements.

---
---

You're right - let me restructure it to match the style with proper numbering:

### 1.11. **Level System**

#### Purpose:
Manages the game's level hierarchy, transitions, and gameplay progression through a base level class and specific implementations.

#### Key Components:
- **Inheritance & Relationships**:
  - `Level_Base` inherits from `eb::World`
  - Specific levels (LevelOne, LevelTwo, etc.) inherit from `Level_Base`
  - Managed by `GameApplication`

- **Level Base Structure**:
  ```cpp
  class Level_Base : public eb::World
  {
      GameApplication* _gameApplication;
      weak_ptr<Player> _player;
      weak_ptr<Ball_Regular> _ballRegular;
      weak_ptr<Block_Boundry> _boundry;
      int _numberOfLevelBlocksRemaining;
      bool _shouldLoadNextLevel;
  };
  ```

- **Level Lifecycle Management**:
  - **Initialization**:
    - Base level setup via constructor
    - Spawning of boundaries, blocks, player, and ball
    - Virtual BeginPlay for level-specific setup

  - **Runtime**:
    - Block counting and destruction tracking
    - Level completion monitoring
    - Actor cleanup and world transition

  - **Transition**:
    - World cleanup through DestroyAllActors
    - Level advancement via GameApplication
    - New level initialization and setup

- **Virtual Functions**:
  - `SpawnBoundryBlocks` - Creates level boundaries
  - `SpawnLevelBlocks` - Defines block patterns
  - `SpawnPlayer` - Places player in level
  - `SpawnBall` - Initializes game ball
  - `Tick` - Handles level-specific updates

#### Level Progression Flow:
1. Level initialization and actor spawning
2. Gameplay and block destruction
3. Level completion check
4. World cleanup and transition
5. Next level creation and setup

Would you like me to elaborate on any particular aspect of this structure?

---
---

# Processes

## 2.1.Calling An Actor 

### Actor Creation  

Actors are created using the `SpawnActor` template function from **World.h** When an actor is spawned, it is added to the `_pendingActors` list, which holds actors that are not yet fully initialized.  

```cpp
template<typename ActorType, typename... Args>
weak_ptr<ActorType> SpawnActor(Args... args)
{
    shared_ptr<ActorType> spawningActor{ new ActorType(this, args...) };
    _pendingActors.push_back(spawningActor);
    return spawningActor;
}
```  

**Key Points**  
- The `SpawnActor` function constructs the actor using the provided arguments.  
- The `this` pointer (the `World` instance) is passed to the actor's constructor, ensuring the actor knows which world it belongs to.  
- The actor is added to `_pendingActors` for later initialization.  

---  

### Actor Initialization  

On the next game tick, actors in `_pendingActors` are moved to `_actors` and initialized.  

#### Process  
1. The `World` iterates through `_pendingActors`.  
2. Each actor is moved to `_actors`.  
3. The `BeginPlayInternal` function is called, which in turn calls the actor's `BeginPlay` method.  

```cpp
void World::Tick(float deltaTime)
{
    // Move pending actors to active actors
    for (auto& actor : _pendingActors)
    {
        _actors.push_back(actor);
        actor->BeginPlayInternal();
    }
    _pendingActors.clear();

    // Update active actors
    for (auto& actor : _actors)
    {
        actor->TickInternal(deltaTime);
    }
}
```  

**Key Points**  
- `BeginPlayInternal` is a wrapper that calls the actor's `BeginPlay` method.  
- This is where world-specific initialization logic for the actor is executed.  

---  

### Actor Updates  

Active actors receive updates every frame via the `Tick` method.  

#### Process  
1. The `World` calls `TickInternal` on each actor in `_actors`.  
2. `TickInternal` calls the actor's `Tick` method, passing the `deltaTime` (time since the last frame).  

```cpp
void Actor::TickInternal(float deltaTime)
{
    if (!_isPendingDestroy)
    {
        Tick(deltaTime);
    }
}
```  

**Key Points**  
- The `Tick` method is where per-frame updates (e.g., movement, physics, etc.) are handled.  
- Actors marked for destruction (`_isPendingDestroy`) are skipped.  

---  

### Actor Destruction  

Actors marked for destruction are cleaned up during the `CleanCycle`.  

#### Process  
1. Actors set their `_isPendingDestroy` flag to `true` when they are no longer needed.  
2. During the `CleanCycle`, the `World` iterates through `_actors` and removes any actors with `_isPendingDestroy` set to `true`.  

```cpp
void World::CleanCycle()
{
    _actors.erase(std::remove_if(_actors.begin(), _actors.end(),
        [](const shared_ptr<Actor>& actor) {
            return actor->IsPendingDestroy();
        }), _actors.end());
}
```  

**Key Points**  
- Actors are responsible for marking themselves for destruction (e.g., via `Destroy`).  
- The `World` handles the actual removal of destroyed actors.  

---  

### World Cleanup  

When the `World` is destroyed, all remaining actors are cleaned up.  

#### Process  
1. The `World` destructor iterates through `_actors` and ensures all actors are properly destroyed.  
2. Any remaining resources are released.  

```cpp
World::~World()
{
    for (auto& actor : _actors)
    {
        actor->Destroy();
    }
    _actors.clear();
}
```  

**Key Points**  
- This ensures no memory leaks occur when the `World` is destroyed.  

---

## Key Methods in Actor Lifecycle  

### `virtual void BeginPlay();`  

**Purpose**: Override point for world-specific initialization.  
**Usage**: Implement this method in derived actors to handle setup logic (e.g., spawning child actors, initializing components).  

```cpp
void Block_Base::BeginPlay()
{
    // Custom initialization logic
}
```  

---  

### `virtual void Tick(float deltaTime);`  

**Purpose**: Override point for world-specific updates.  
**Usage**: Implement this method in derived actors to handle per-frame updates (e.g., movement, input handling).  

```cpp
void Block_Base::Tick(float deltaTime)
{
    // Custom update logic
}
```  

---

## Example: Spawning and Using an Actor  

### Spawning an Actor  

In your `LevelOne` class, you can spawn an actor like this:  

```cpp
LevelOne::LevelOne(Application* owningApplication)
    : World{ owningApplication }
{
    _testActor = SpawnActor<Block_Base>(sf::Vector2f{ 400, 100 }, sf::Color::Red);
    _testActor.lock()->SetActorLocation(sf::Vector2f(300.f, 500.f));
}
```  

**Key Points**  
- `SpawnActor` creates a `Block_Base` actor and passes the `World` (`this`) to its constructor.  
- The actor is added to `_pendingActors` and initialized on the next tick.  

---

### Overriding `BeginPlay` and `Tick`  

In your `Block_Base` class, you can override `BeginPlay` and `Tick` to add custom behavior:  

```cpp
void Block_Base::BeginPlay()
{
    // Initialization logic
    PRINT("Block_Base BeginPlay!");
}

void Block_Base::Tick(float deltaTime)
{
    // Update logic
    SetActorLocation(GetActorLocation() + sf::Vector2f(1.f, 0.f)); // Move right
}
```  

---

### Destroying an Actor  

To destroy an actor, call its `Destroy` method:  

```cpp
void Block_Base::SomeFunction()
{
    if (ShouldDestroy())
    {
        Destroy(); // Mark for destruction
    }
}
```  

**Key Points**  
- The actor will be removed during the next `CleanCycle`.  

---

## Summary of Actor Lifecycle  

- **Creation**: Actors are spawned via `SpawnActor` and added to `_pendingActors`.  
- **Initialization**: On the next tick, actors are moved to `_actors` and `BeginPlay` is called.  
- **Updates**: Active actors receive `Tick` calls every frame.  
- **Destruction**: Actors marked for destruction are removed during `CleanCycle`.  
- **Cleanup**: The `World` destructor ensures all actors are properly destroyed.  

---
---

# Physics System 

## 3.1. Physics System Overview

The physics system in the engine uses Box2D for simulation and provides a seamless integration with SFML graphics. It manages:
- Physics body creation and destruction
- Collision detection and responses
- Coordinate system conversion between pixels and meters
- Debug visualization

## 3.2. Key Components

### PhysicsSystem
- Singleton class managing the Box2D world
- Handles physics body lifecycle
- Provides coordinate conversion utilities
- Configurable simulation parameters

### PhysicsContactListener
- Manages collision events between actors
- Provides Begin/End overlap notifications
- Automatically triggers actor overlap events

## 3.3. Actor Physics Integration

### Enabling Physics
```cpp
// In your actor class
void YourActor::BeginPlay()
{
    SetPhysicsEnabled(true);  // Automatically creates physics body
}
```

### Physics Properties
- Default configuration:
  - Dynamic body type
  - Density: 1.0f
  - Friction: 0.3f
  - Sensor mode enabled (triggers overlaps without physical collision)
  - Zero gravity environment

### Debug Visualization
- Red outline shows physics body bounds
- Enable/disable via `_debugDrawEnabled` flag in Actor.h
- Helps verify physics/visual alignment

## 3.4. Coordinate Systems

### Physics Scale
- Box2D works in meters
- SFML works in pixels
- Default scale: 32 pixels = 1 meter
- Conversion handled automatically via:
  ```cpp
  // Converting between coordinate systems
  float metersValue = PhysicsSystem::Get().PixelsToMetersValue(pixelsValue);
  float pixelsValue = PhysicsSystem::Get().MetersToPixelsValue(metersValue);
  ```

## 3.5. Physics Events

### Overlap Events
```cpp
// Override in your actor class
void OnActorBeginOverlap(Actor* hitActor) override
{
    // Called when physics bodies start overlapping
}

void OnActorEndOverlap(Actor* hitActor) override
{
    // Called when physics bodies stop overlapping
}
```

## 3.6. Implementation Example

```cpp
class PhysicsActor : public Actor
{
public:
    PhysicsActor(World* world) : Actor(world)
    {
        SetPhysicsEnabled(true);  // Enable physics
    }

    void BeginPlay() override
    {
        // Physics is now initialized
    }

    void OnActorBeginOverlap(Actor* other) override
    {
        // Handle collision start
    }

    void OnActorEndOverlap(Actor* other) override
    {
        // Handle collision end
    }
};
```

## 3.7. Physics Synchronization

### Actor-to-Physics
- Called when manually moving actor
- Updates physics body position/rotation
- Handles coordinate conversion automatically
```cpp
void SetActorLocation(const sf::Vector2f& newLocation);
void SetActorRotation(const float newRotation);
```

### Physics-to-Actor
- Called each frame during actor tick
- Updates visual representation to match physics
- Handles coordinate conversion automatically
```cpp
void SyncWithPhysics();  // Called automatically in Tick
```

## 3.8. Best Practices

1. **Initialization**
   - Enable physics in BeginPlay
   - Verify debug visualization alignment
   - Set initial position before enabling physics

2. **Movement**
   - Use SetActorLocation for immediate positioning
   - Let physics handle continuous movement
   - Remember to handle rotation if needed

3. **Cleanup**
   - Physics automatically disabled on actor destruction
   - No manual cleanup needed for normal usage

4. **Debug**
   - Enable debug drawing during development
   - Verify physics bounds match visual bounds
   - Check scale factor if alignments seem off

## 3.9. Common Issues and Solutions

1. **Misaligned Visuals**
   - Verify center offset calculations
   - Check physics scale factor
   - Enable debug visualization

2. **Overlap Not Detecting**
   - Verify both actors have physics enabled
   - Check if fixtures are set as sensors
   - Ensure actors aren't pending destroy

3. **Performance**
   - Adjust velocity/position iterations
   - Disable physics when not needed
   - Use appropriate scale factors