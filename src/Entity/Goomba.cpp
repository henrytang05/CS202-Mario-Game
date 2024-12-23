#include "Components/Components_include.h"
#include "Entity/Mario.h"

Weak<AbstractEntity> initGoomba(EntityManager &EM, Vector2 position,
                                Vector2 size) {
  static int cnt = 1;
  std::string name = "Goomba" + std::to_string(cnt++);

  Weak<AbstractEntity> rEnemy = EM.createEntity(name);
  Shared<AbstractEntity> enemy = rEnemy.lock();

  enemy->addComponent<CollisionComponent>();

  enemy->addComponent<PositionComponent>(position);

  enemy->addComponent<TransformComponent>(Vector2{-10.0f * cnt, 10});
  enemy->addComponent<BoundingBoxComponent>(size);
  enemy->addComponent<EnemyTag>();
  enemy->addComponent<TextureComponent>();

  std::vector<Texture2D> textures{
      LoadTexture("assets/Goomba/Goomba-Left-Idle.png"),
      LoadTexture("assets/Goomba/Goomba-Left-Moving.png")};
  enemy->getComponent<TextureComponent>().addTexture("Left-Moving", textures,
                                                     0.1f, true);

  enemy->getComponent<TextureComponent>().addTexture(
      "Right-Moving",
      {LoadTexture("assets/Goomba/Goomba-Right-Idle.png"),
       LoadTexture("assets/Goomba/Goomba-Right-Moving.png")},
      0.1f, true);

  enemy->getComponent<TextureComponent>().addTexture(
      "Die", {LoadTexture("assets/Goomba/Goomba-Die.png")}, .3f, false);

  enemy->getComponent<TextureComponent>().changeState("Left-Moving");

  return enemy;
}
