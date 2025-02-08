# Engine Project Documentation

## Index

1.Application.h
2.Application.cpp
3.EntryPoint.h
4.EntryPoint.cpp
5.Core.h
6.World.h
7.GameApplication.h
8.GameApplication.cpp
9.Object.h

---

## File Structure

### 1. **Application.h**
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

### 2. **Application.cpp**
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

### 3. **EntryPoint.h**
#### **Purpose**:
Declares an external function to retrieve the `Application` instance.

#### **Key Components**:
- `extern eb::Application* GetApplication();` - Entry point to create an `Application` instance.

---

### 4. **EntryPoint.cpp**
#### **Purpose**:
Defines the main entry point of the application.

#### **Key Components**:
- Calls `GetApplication()` to create the game instance.
- Calls `RunMainLoop()`.
- Deletes the `Application` instance after execution.

---

### 5. **Core.h**
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

### 6. **World.h**
#### **Purpose**:
Currently a placeholder header file for world-related functionality.

---

### 7. **GameApplication.h**
#### **Purpose**:
Defines `GameApplication`, which inherits from `Application`.

#### **Key Components**:
- `class GameApplication : public eb::Application` - Custom game-specific application class.
- Constructor: `GameApplication();`

---

### 8. **GameApplication.cpp**
#### **Purpose**:
Implements `GameApplication` and provides an instance of it.

#### **Key Components**:
- `GameApplication::GameApplication()`:
  - Initializes the application with resolution `1920x1080`.
  - Enables `Resize` and `Close` window styles.
- `eb::Application* GetApplication()`:
  - Returns a new `GameApplication` instance.

---

### 9. **Object.h**
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