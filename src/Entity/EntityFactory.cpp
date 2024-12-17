#include "Entity/EntityFactory.h"

#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/EnemyComponents.h"
#include "Components/Texture.h"
#include "Entity/PlayableEntity.h"
#include "pch.h"
#include <memory>

Shared<Mario> EntityFactory::createMario() {
  Shared<Mario> mario = std::make_shared<Mario>();

  return mario;
}
Shared<Luigi> EntityFactory::createLuigi() {
  Shared<Luigi> luigi = std::make_shared<Luigi>();
  return luigi;
}
Shared<AbstractEntity> EntityFactory::createGoomba() {
  // Shared<Entity> goomba = std::make_shared<Entity>();
  // // TODO: Add components
  // return goomba;
  return nullptr;
}

Shared<Enemy> EntityFactory::createEnemy(Vector2 position, Vector2 size) {
  static int cnt = 1;
  std::string name = "Goomba" + std::to_string(cnt++);
  Shared<Enemy> enemy = std::make_shared<Enemy>(name);

  enemy->addComponent<EnemyPosition>(position);
  enemy->addComponent<EnemyVelocity>(Vector2{-1.0f, 0});
  enemy->addComponent<EnemySize>(size);
  enemy->addComponent<CollisionComponent>();
  enemy->addComponent<EnemyTag>();

  enemy->addComponent<TextureComponent>();
  enemy->getComponent<TextureComponent>().addTexture(
      "Goomba-Die", "./assets/Goomba/Goomba-Die.png");

  enemy->getComponent<TextureComponent>().addTexture(
      "Goomba-Left-Idle", "./assets/Goomba/Goomba-Left-Idle.png");
  enemy->getComponent<TextureComponent>().addTexture(
      "Goomba-Right-Idle", "./assets/Goomba/Goomba-Right-Idle.png");

  enemy->getComponent<TextureComponent>().addTexture(
      "Goomba-Left-Moving", "./assets/Goomba/Goomba-Left-Moving.png");
  enemy->getComponent<TextureComponent>().addTexture(
      "Goomba-Right-Moving", "./assets/Goomba/Goomba-Right-Moving.png");
  return enemy;
}

Shared<AbstractEntity>
EntityFactory::createBlock(string type, Texture2D texture, Vector2 position) {
  std::cerr << "Still good get into createBlock" << std::endl;
  Shared<AbstractEntity> block = nullptr;
  if (type == "NormalBlock") {
    block = std::make_shared<NormalBlock>(texture, position);
  } else if (type == "BrokenBlock") {
    block = std::make_shared<BrokenBlock>(texture, position);
  } else if (type == "HardBlock") {
    block = std::make_shared<HardBlock>(texture, position);
  } else if (type == "GroundBlock") {
    block = std::make_shared<GroundBlock>(texture, position);
  } else if (type == "QuestionBlock") {
    block = std::make_shared<QuestionBlock>(texture, position);
  }
  block->addComponent<StillObjectTag>();
  return block;
}

Shared<AbstractEntity> EntityFactory::createPipe(Vector2 position,
                                                 Vector2 size) {
  Shared<AbstractEntity> pipe = std::make_shared<Pipe>(position, size);
  pipe->addComponent<StillObjectTag>();
  return pipe;
}

Shared<AbstractEntity> EntityFactory::createFlag(Vector2 position) {
  Shared<AbstractEntity> flag = std::make_shared<Flag>(position);

  flag->addComponent<StillObjectTag>();
  return flag;
}
