#include "Entity/Enemy.h"

void handleCollision() {
  // CollisionComponent &collision = getComponent<CollisionComponent>();
  // auto above = collision.getAbove();
  // auto below = collision.getBelow();
  // auto left = collision.getLeft();
  // auto right = collision.getRight();
  //
  // auto &trans = getComponent<TransformComponent>();
  //
  // Vector2 v = trans.getVelocity();
  // if (left && !left->hasComponent<EnemyTag>())
  //   v.x = ENEMY_SPEED;
  // else if (right && !right->hasComponent<EnemyTag>())
  //   v.x = -ENEMY_SPEED;
  //
  // if (!below) {
  //   if (getComponent<PositionComponent>().getY() > screenHeight) {
  //     destroy();
  //     getComponent<TextureComponent>().changeState("Die");
  //   }
  // }
  // trans.setVelocity(v);
  // if (above != nullptr) {
  //   if (above->hasComponent<PlayerTag>()) {
  //     destroy();
  //     getComponent<TextureComponent>().changeState("Die");
  //   }
  // }
  // getComponent<CollisionComponent>().reset();
}
