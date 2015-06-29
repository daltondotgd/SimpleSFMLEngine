# Lightweight, Simple SFML Engine

## Todo list

1. ~~Core engine~~
1. ~~Advanced scene tree~~
1. ~~Shaders handling~~
1. ~~Text object~~
1. ~~Vector math~~
1. ~~Camera~~
1. ~~HUD~~
1. Input manager - mouse, keyboard & pad (almost ready, will be added with configs)
1. Simple physics and collision handling (almost ready - collisions already implemented, physics engine under construction)
1. Sounds and music advanced support (simple support already in)
1. Simple tile maps support
1. Game!

## Maybe

1. ~~Actions~~
1. Configs (lib almost ready, need to be added to the engine)
1. Scripting
1. Threading `// nope`

```cpp
// Starting engine
Engine::getInstance().init(sf::VideoMode(800, 600), "Best game evar!", 60, gameWorld, sf::Style::None, settings, false);
/*
 * 1. Video mode
 * 2. Title
 * 3. FPS limit
 * 4. World
 * 5. Style
 * 6. ContextSettings
 * 7. Vertical sync
 */
```

```cpp
// Adding children
Node::add(Node* node);
```

```cpp
// Getting time in seconds

// In constructor - remember to include "Engine.h"
Engine::getInstance().deltaTime();
Engine::getInstance().globalTime();

// In init(), update() and draw(...) or methods called by them
getEngine().deltaTime();
getEngine().globalTime();
```

```cpp
/*
 * Node methods to be overdriven
 */
 
// Called after node is being added to scene - you gain access to return values getEngine() and getParent() here
virtual void init();
// Called every frame for updating your Node
virtual void update();
// Called every frame for drawing your Node
virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states);
```

```cpp
// Object classes - can be added to scene
class AnimatedSprite;
class FPSCounter;
class Node;
class Sprite;
class Text;
class World;
--------------- TODO ---------------
// class Action;
```