#ifndef ENEMY_COMPONENTS_H
#define ENEMY_COMPONENTS_H

#include "Components/Collision.h"
#include "Components/Component.h"
#include "Components/Texture.h"
#include "raylib.h"

struct EnemyPosition : public Vector2, public Component {
  EnemyPosition() : Vector2(), Component("EnemyPosition") {}
  EnemyPosition(Vector2 pos) : Vector2(pos), Component("EnemyPosition") {}
};

struct EnemyVelocity : public Vector2, public Component {
  EnemyVelocity() : Vector2(), Component("EnemyVelocity") {}
  EnemyVelocity(Vector2 vel) : Vector2(vel), Component("EnemyVelocity") {}
};

struct EnemySize : public Vector2, public Component {
  EnemySize() : Vector2(), Component("EnemySize") {};
  EnemySize(Vector2 size) : Vector2(size), Component("EnemySize") {}
};

// struct EnemyTexture : public TextureComponent {
//   EnemyTexture() : TextureComponent() {}
//   std::map<std::string, Texture2D> textures;
// };

struct EnemyCollision : public CollisionComponent {
  EnemyCollision() : CollisionComponent() {}
};

struct EnemyTag : public Component {
  EnemyTag() : Component("EnemyTag") {}
};

struct PlayerTag : public Component {
  PlayerTag() : Component("PlayerTag") {}
};

struct StillObjectTag : public Component {
  StillObjectTag() : Component("StillObjectTag") {}
};

#endif // ENEMY_COMPONENTS_H
