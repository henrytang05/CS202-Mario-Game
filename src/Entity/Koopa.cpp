#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Position.h"
#include "Entity/Enemy.h"
#include "EntityManager.h"
#include "globals.h"

Weak<AbstractEntity> initKoopa(Vector2 position, Vector2 size) {
  EntityManager &EM = EntityManager::getInstance();
  Weak<AbstractEntity> _koopa = EM.createEntity("Koopa");
  ASSERT(!_koopa.expired(), "Failed to create Koopa entity");

  auto koopa = _koopa.lock();
  koopa->addComponent<PositionComponent>(position);
  koopa->addComponent<TransformComponent>(Vector2{-ENEMY_SPEED, 10});
  koopa->addComponent<BoundingBoxComponent>(size);

  koopa->addComponent<CollisionComponent>();

  return _koopa;
}
