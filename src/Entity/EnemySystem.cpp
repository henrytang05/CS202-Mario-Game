#include "Entity/EnemySystem.h"

#include "AbstractEntity.h"
#include "Components/Collision.h"
#include "Components/EnemyComponents.h"
#include "Components/Texture.h"
#include "globals.h"
#include "raylib.h"

EnemyAISystem createEnemyAISystem() {
  return [](EnemyPosition &position, EnemyVelocity &velocity, EnemySize &size) {
    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x < 0) {
      velocity.x = 1;
    }
    if (position.x > 1920) {
      velocity.x = -1;
    }
    if (position.y < 0) {
      velocity.y = 1;
    }
    if (position.y > 1080) {
      velocity.y = -1;
    }
  };
}

EnemyRenderSystem createEnemyRenderSystem() {
  // NOTE: when is Goomba idle
  return [](EnemyPosition &position, EnemyVelocity &velocity,
            TextureComponent &texture, int dt) {
    Vector2 pos = {position.x, position.y};
    Vector2 vel = {velocity.x, velocity.y};
    std::string direction;
    std::string state;
    if (dt & 1) {
      state = "Idle";
    } else {
      state = "Moving";
    }
    if (vel.x > 0) {
      direction = "Right";
    } else {
      direction = "Left";
    }
    std::string textStr = "Goomba-" + direction + "-" + state;
    DrawTexture(texture.textures[textStr], pos.x, pos.y, WHITE);
  };
}

EnemyCollisionSystem createEnemyCollisionSystem() {
  return [](CollisionComponent &c, EnemyPosition &pos, EnemyVelocity &vel,
            TextureComponent &texture, AbstractEntity &entity) {
    Shared<AbstractEntity> collisionAbove = c.collisionAbove();
    if (collisionAbove) {
      if (collisionAbove->hasComponent<PlayerTag>()) {
        DrawTexture(texture.textures["Goomba-Die"], pos.x, pos.y, WHITE);
        entity.destroy();
        return;
      }
    }

    Shared<AbstractEntity> collisionSide = c.collisionSide();
    if (collisionSide) {
      if (collisionSide->hasComponent<StillObjectTag>()) {
        vel.x = -vel.x;
        return;
      }
    }

    // TODO: check for stading on ground
    Shared<AbstractEntity> standingOn = c.standingOn();
  };
}
