#include "Entity/Enemy.h"
#include "Components/Components_include.h"


// TODO: change to goomba
Weak<AbstractEntity> initGoomba(Vector2 position, Vector2 size) {
  EntityManager &EM = EntityManager::getInstance();
  static int cnt = 1;
  std::string name = "Goomba";

  // TODO: change to make shared
  Weak<AbstractEntity> rEnemy = EM.createEntity(name);
  Shared<AbstractEntity> enemy = rEnemy.lock();

  enemy->addComponent<CollisionComponent>();
  enemy->addComponent<PositionComponent>(position);
  enemy->addComponent<TransformComponent>(Vector2{-ENEMY_SPEED, 10});
  enemy->addComponent<BoundingBoxComponent>(size);
  enemy->addComponent<EnemyTag>();
  enemy->addComponent<AITag>();
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

void Goomba::changeState() {
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