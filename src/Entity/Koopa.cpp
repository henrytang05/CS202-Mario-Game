#include "Components/Components_include.h"
#include "Entity/Enemy.h"
#include "EntityManager.h"
#include "globals.h"
#include "raylib.h"

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

  std::string koopaPath = "assets/Koopa/";

  std::string koopaLeftIdle = koopaPath + "Koopa-Left-Idle.png";
  std::string koopaLeftMoving = koopaPath + "Koopa-Left-Moving.png";
  std::string koopaRightIdle = koopaPath + "Koopa-Right-Idle.png";
  std::string koopaRightMoving = koopaPath + "Koopa-Right-Moving.png";
  std::string shellKoopaIdle = koopaPath + "Shell-Koopa-Idle.png";
  std::string shellKoopaMoving = koopaPath + "Shell-Koopa-Idle.png";
  std::string shellKoopaMoving2 = koopaPath + "Shell-Koopa-Moving.png";
  std::string shellKoopaMoving3 = koopaPath + "Shell-Koopa-Moving2.png";

  std::vector<Texture2D> textures = {
      LoadTexture(koopaLeftIdle.c_str()),
      LoadTexture(koopaLeftMoving.c_str()),
  };

  koopa->getComponent<TextureComponent>().addTexture("Left-Moving", textures,
                                                     0.1f, true);

  textures = {
      LoadTexture(koopaRightIdle.c_str()),
      LoadTexture(koopaRightMoving.c_str()),
  };

  koopa->getComponent<TextureComponent>().addTexture("Right-Moving", textures,
                                                     0.1f, true);

  koopa->getComponent<TextureComponent>().addTexture(
      "Die", {LoadTexture(shellKoopaIdle.c_str())}, .3f, false);

  textures = {
      LoadTexture(shellKoopaMoving.c_str()),
      LoadTexture(shellKoopaMoving2.c_str()),
      LoadTexture(shellKoopaMoving3.c_str()),
  };

  koopa->getComponent<TextureComponent>().addTexture("Shell", textures,
                                                     0.1f, true);

  koopa->getComponent<TextureComponent>().addTexture("Shell-Moving", textures,
                                                     0.1f, true);

  koopa->getComponent<TextureComponent>().changeState("Left-Moving");

  return _koopa;
}
