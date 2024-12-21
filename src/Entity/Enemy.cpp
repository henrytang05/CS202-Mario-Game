#include "Entity/Enemy.h"

#include "AbstractEntity.h"
#include "Components/Collision.h"
#include "Components/EnemyComponents.h"
#include "Components/Gravity.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "globals.h"
#include "raylib.h"

Enemy::Enemy(std::string name) : AbstractEntity(name) {
  // Initialize enemy
}
void Enemy::update(float deltatime) {
  for (auto &component : components) {
    component->update(deltatime);
  }

  handleCollision();
}

void Enemy::handleCollision() {
  CollisionComponent &collision = getComponent<CollisionComponent>();
  auto above = collision.getAbove();
  auto below = collision.getBelow();
  auto left = collision.getLeft();
  auto right = collision.getRight();

  auto &trans = getComponent<TransformComponent>();

  Vector2 v = trans.getVelocity();
  if (left && !left->hasComponent<EnemyTag>())
    v.x = ENEMY_SPEED;
  else if (right && !right->hasComponent<EnemyTag>())
    v.x = -ENEMY_SPEED;

  if (!below) {
    if (getComponent<PositionComponent>().getY() > screenHeight) {
      destroy();
      getComponent<Animation>().changeState("Goomba-Die");
    }
  }
  trans.setVelocity(v);
  if (above != nullptr) {
    if (above->hasComponent<PlayerTag>()) {
      destroy();
      getComponent<Animation>().changeState("Goomba-Die");
    }
  }
  getComponent<CollisionComponent>().reset();
}

void Enemy::draw() {
  // for (auto &component : components) {
  //   component->draw();
  // }
}
