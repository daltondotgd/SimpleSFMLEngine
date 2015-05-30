# Lightweight, Simple SFML Engine

## Todo list

1. Text object
1. Input manager - mouse, keyboard & pad
1. Vector math
1. Sounds and music advanced support
1. Simple tile maps support
1. Simple physics and collision handling
1. Game!

## Maybe

1. Configs
1. Scripting
1. Actions
1. Threading

```cpp
// Starting engine
Engine::getInstance().init(sf::VideoMode(800, 600), "Best game evar!", 60, gameWorld);
/*
 * 1. Video mode
 * 2. Title
 * 3. FPS limit
 * 3. World
 */
```

```cpp
// Adding children
Node::add(Node* node);
```

```cpp
// Node methods to be overdriven
virtual void init();															// Called whed node is being added to scene
virtual void update();															// Called every frame
virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states);	// Called every frame
```

```cpp
// Object classes - can be added to scene
class AnimatedSprite;
class FPSCounter;
class Node;
class Sprite;
class World;
--------------- TODO ---------------
// class Action;
// class Text;
```