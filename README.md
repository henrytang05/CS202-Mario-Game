# Mario Game

This is a Mario game project built using C++ and the Raylib library. The project includes various scenes, entities, and components to create a complete game experience.

## Object-Oriented Programming (OOP)

The project is designed with OOP principles in mind, ensuring modularity, reusability, and maintainability. Key OOP concepts used in this project include:

- **Encapsulation**: Each class encapsulates its data and provides public methods to interact with that data. For example, the [`SceneSpace::RankingScene`](include/Scenes/RankingScene.h) class encapsulates the logic for the ranking scene.
- **Inheritance**: Classes inherit from base classes to reuse and extend functionality. For example, [`SceneSpace::RankingScene`](include/Scenes/RankingScene.h) inherits from the [`Scene`](include/Scenes/Scene.h) class.
- **Polymorphism**: The project uses polymorphism to allow different classes to be treated as instances of the same base class. For example, the `updateScene` method in [`Scene`](include/Scenes/Scene.h) is overridden in [`SceneSpace::RankingScene`](include/Scenes/RankingScene.h).

## Design Patterns

Several design patterns are employed in this project to solve common software design problems:

### Singleton Pattern

The Singleton pattern ensures that a class has only one instance and provides a global point of access to it. This pattern is used in the [`EntityManager`](include/EntityManager.h) and [`EventQueue`](include/EventManager.h) classes.

```cpp
// Example of Singleton pattern in EntityManager
class EntityManager {
public:
  static EntityManager& getInstance() {
    static EntityManager instance;
    return instance;
  }
  // Other methods...
private:
  EntityManager() {}
  // Prevent copying
  EntityManager(const EntityManager&) = delete;
  void operator=(const EntityManager&) = delete;
};
```

### Factory Pattern

The Factory pattern is used to create objects without specifying the exact class of the object that will be created. This pattern is used in the [`EntityFactory`](include/Entity/EntityFactory.h) class to create different game entities.

```cpp
// Example of Factory pattern in EntityFactory
class EntityFactory {
public:
  Unique<AbstractEntity> createMario() {
    return std::make_unique<Mario>();
  }
  // Other factory methods...
};
```

### Observer Pattern

The Observer pattern is used to notify multiple objects about state changes. This pattern is implemented in the event handling system, where events are pushed to the [`EventQueue`](include/EventManager.h) and processed by various systems.

```cpp
// Example of Observer pattern in EventQueue
class EventQueue {
public:
  void pushEvent(Unique<Event> e) {
    events.push(std::move(e));
  }
  void processAllEvents() {
    while (!events.empty()) {
      events.front()->handle();
      events.pop();
    }
  }
  // Other methods...
private:
  std::queue<Unique<Event>> events;
};
```

### Component Pattern

The Component pattern is used to build complex objects by combining simpler ones. This pattern is used extensively in the entity-component-system (ECS) architecture of the game. Entities are composed of various components such as [`TransformComponent`](include/Components/TransformComponent.h), [`TextureComponent`](include/Components/TextureComponent.h), and [`CharacterStateComponent`](include/Components/CharacterStateComponent.h).

```cpp
// Example of Component pattern in an entity
class Mario : public AbstractEntity {
public:
  Mario() {
    addComponent<TransformComponent>();
    addComponent<TextureComponent>();
    addComponent<CharacterStateComponent>();
    // Other components...
  }
  // Other methods...
};
```

## Key Components

### Scenes

- **RankingScene**: Handles the ranking display.
  - Header: [include/Scenes/RankingScene.h](include/Scenes/RankingScene.h)
  - Source: [src/Scenes/RankingScene.cpp](src/Scenes/RankingScene.cpp)

#### Excerpt from `RankingScene.h`

```cpp
#ifndef RANKINGSCENE_H
#define RANKINGSCENE_H

#include "GUI.h"
#include "Scenes/Scene.h"

namespace SceneSpace {
class RankingScene : public Scene {
public:
  RankingScene();
  ~RankingScene();
  Unique<SceneSpace::Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;
```

- **ChooseThemeScene**: Allows the player to choose a theme.
  - Header: [include/Scenes/ChooseThemeScene.h](include/Scenes/ChooseThemeScene.h)
  - Source: [src/Scenes/ChooseThemeScene.cpp](src/Scenes/ChooseThemeScene.cpp)

- **IntroScene**: The introductory scene of the game.
  - Source: [src/Scenes/IntroScene.cpp](src/Scenes/IntroScene.cpp)

### External Libraries

- **Raylib**: A simple and easy-to-use library to enjoy videogames programming.
  - Header: [include/raylib.h](include/raylib.h)

## Building the Project

To build the project, run the following command:

```sh
make
```

This will compile the source code and generate the `Mario.exe` executable.

## Running the Game

After building the project, you can run the game using the following command:

```sh
./Mario.exe
```

## License

This project is licensed under the zlib/libpng license. See the [raylib.h](include/raylib.h) file for more details.

## Acknowledgments

- [Raylib](https://www.raylib.com) for providing the game development library.
- All contributors and maintainers of the external libraries used in this project.
