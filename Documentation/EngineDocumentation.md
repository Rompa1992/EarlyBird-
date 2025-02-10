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

### Processes
2.1.Calling An Actor 

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
  - Returns the window’s size from SFML’s `RenderWindow`.

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

