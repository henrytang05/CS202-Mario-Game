#include "Entity/EntityFactory.h"

#include "Components/Components_include.h"
#include "raylib.h"

EntityFactory::EntityFactory() : IFactory(), EM(EntityManager::get()) {}
//
AbstractEntity &EntityFactory::createMario() {}
// AbstractEntity &EntityFactory::createLuigi() {
//   AbstractEntity &();
//   return luigi;
// }
// AbstractEntity &EntityFactory::createGoomba() {
//   // AbstractEntity&();
//   // // TODO: Add components
//   // return goomba;
//   return nullptr;
// }

AbstractEntity &EntityFactory::createEnemy(Vector2 position, Vector2 size) {
  static int cnt = 1;
  std::string name = "Goomba" + std::to_string(cnt++);

  AbstractEntity &enemy = EM.createEntity(name);

  EM.addComponent<CollisionComponent>(&enemy);

  EM.addComponent<PositionComponent>(&enemy, position);

  EM.addComponent<TransformComponent>(&enemy, Vector2{-10.0f * cnt, 10});
  EM.addComponent<BoundingBoxComponent>(&enemy, size);
  EM.addComponent<EnemyTag>(&enemy);
  EM.addComponent<Gravity>(&enemy);
  EM.addComponent<TextureComponent>(&enemy);

  std::vector<Texture2D> textures{
      LoadTexture("assets/Goomba/Goomba-Left-Idle.png"),
      LoadTexture("assets/Goomba/Goomba-Left-Moving.png")};
  EM.getComponent<TextureComponent>(&enemy).addTexture("Left-Moving", textures,
                                                       0.1f, true);

  EM.getComponent<TextureComponent>(&enemy).addTexture(
      "Right-Moving",
      {LoadTexture("assets/Goomba/Goomba-Right-Idle.png"),
       LoadTexture("assets/Goomba/Goomba-Right-Moving.png")},
      0.1f, true);

  EM.getComponent<TextureComponent>(&enemy).addTexture(
      "Die", {LoadTexture("assets/Goomba/Goomba-Die.png")}, .3f, false);

  EM.getComponent<TextureComponent>(&enemy).changeState("Left-Moving");

  // EM.getComponent<TextureComponent2>(&enemy, ).addTexture(
  //     "Goomba-Die", "./assets/Goomba/Goomba-Die.png");
  //
  // EM.getComponent<TextureComponent2>(&enemy, ).addTexture(
  //     "Goomba-Left-Idle", "./assets/Goomba/Goomba-Left-Idle.png");
  // EM.getComponent<TextureComponent2>(&enemy, ).addTexture(
  //     "Goomba-Right-Idle", "./assets/Goomba/Goomba-Right-Idle.png");
  //
  // enemy->getComponent<TextureComponent2>().addTexture(
  //     "Goomba-Left-Moving", "./assets/Goomba/Goomba-Left-Moving.png");
  // enemy->getComponent<TextureComponent2>().addTexture(
  //     "Goomba-Right-Moving", "./assets/Goomba/Goomba-Right-Moving.png");
  return enemy;
}

AbstractEntity &EntityFactory::createBlock(string type, Vector2 position) {
  Texture2D texture = TextureManager::getInstance().getTexture(type);
  std::cerr << "Still good get into createBlock" << std::endl;
  AbstractEntity &block = nullptr;
  if (type == "NormalBlock") {
    block = std::make_shared<NormalBlock>(position);
  } else if (type == "BrokenBlock") {
    block = std::make_shared<BrokenBlock>(position);
  } else if (type == "HardBlock") {
    block = std::make_shared<HardBlock>(position);
  } else if (type == "GroundBlock") {
    block = std::make_shared<GroundBlock>(position);
  } else if (type == "QuestionBlock") {
    block = std::make_shared<QuestionBlock>(position);
  }
  return block;
}

AbstractEntity &EntityFactory::createPipe(Vector2 position, Vector2 size) {
  AbstractEntity &(position, size);
  pipe->addComponent<StillObjectTag>();
  return pipe;
}

AbstractEntity &EntityFactory::createFlag(Vector2 position) {
  AbstractEntity &(position);

  flag->addComponent<StillObjectTag>();
  return flag;
}

AbstractEntity &EntityFactory::createFlagPole(Vector2 position) {
  AbstractEntity &(position);
  return flagPole;
}
