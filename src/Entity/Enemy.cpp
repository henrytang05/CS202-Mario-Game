#include "Entity/Enemy.h"
#include "Components/Collision.h"
#include "Components/Position.h"
#include "Components/Tags.h"
#include "Components/Texture.h"

Enemy::Enemy(std::string name) : AbstractEntity(name) { initEntity(); }

void Enemy::changeState() {
  auto collision = getComponent<CollisionComponent>();
  auto _above = collision.getAbove();
  if (_above.expired())
    throw std::runtime_error("Entity is expired");
  auto above = _above.lock();

  if (above != nullptr) {
    if (above->hasComponent<PlayerTag>()) {
      destroy();
      getComponent<TextureComponent>().changeState("Die");
    }
  }
  getComponent<CollisionComponent>().reset();
}

Koopa::Koopa(Vector2 position, Vector2 size) : Enemy("Koomba") {
  initEntity();
  addComponent<CollisionComponent>();
  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(Vector2{-10.0f, 10});
  // addComponent<TextureComponent>("Koomba", size);
}

void Koopa::changeState() {
  //   auto collision = getComponent<CollisionComponent>();
  //   auto _above = collision.getAbove();
  //   if (_above.expired())
  //     throw std::runtime_error("Entity is expired");
  //   auto above = _above.lock();
  //   // change state
  //
  //   getComponent<CollisionComponent>().reset();
  // }
  //
  // Weak<Koomba> initKoopa(Vector2 position, Vector2 size) {
  //   Shared<Koomba> koomba = std::make_shared<Koomba>(position, size);
  //
  //   koomba->addComponent<CollisionComponent>();
  //   koomba->addComponent<PositionComponent>(position);
  //   koomba->addComponent<TransformComponent>(Vector2{-10.0f, 10});
  //
  //   return koomba;
}

Weak<Koopa> initKoopa(Vector2 position, Vector2 size) {
  return std::make_shared<Koopa>(position, size);
}
