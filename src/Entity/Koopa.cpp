#include "Components/Components_include.h"
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

  koopa->addComponent<EnemyTag>();
  koopa->addComponent<AITag>();
  koopa->addComponent<CollisionComponent>();

  koopa->addComponent<TextureComponent>();

  std::vector<Texture2D> textures{
      LoadTexture("assets/Goomba/Goomba-Left-Idle.png"),
      LoadTexture("assets/Goomba/Goomba-Left-Moving.png")};
  koopa->getComponent<TextureComponent>().addTexture("Left-Moving", textures,
                                                     0.1f, true);

  koopa->getComponent<TextureComponent>().addTexture(
      "Right-Moving",
      {LoadTexture("assets/Goomba/Goomba-Right-Idle.png"),
       LoadTexture("assets/Goomba/Goomba-Right-Moving.png")},
      0.1f, true);

  koopa->getComponent<TextureComponent>().addTexture(
      "Die", {LoadTexture("assets/Goomba/Goomba-Die.png")}, .3f, false);

  koopa->getComponent<TextureComponent>().changeState("Left-Moving");

  return _koopa;
}
