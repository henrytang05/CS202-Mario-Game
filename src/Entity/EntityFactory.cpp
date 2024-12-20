#include "Entity/EntityFactory.h"

#include "Components/Components_include.h"
#include "Entity/PlayableEntity.h"
#include "Entity/Mario.h"
#include "Entity/Luigi.h"
#include "pch.h"
#include <memory>

#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/EnemyComponents.h"
#include "Components/Gravity.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Entity/PlayableEntity.h"
#include "Entity/Mario.h"
#include "Entity/Luigi.h"
#include "pch.h"

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
    if (cnt > 1) return nullptr;
    std::string name = "Goomba" + std::to_string(cnt++);
    Shared<Enemy> enemy = std::make_shared<Enemy>(name);

    enemy->addComponent<CollisionComponent>();
    enemy->addComponent<PositionComponent>(position);
    enemy->addComponent<TransformComponent>(Vector2{-10.0f * cnt, 10});
    enemy->addComponent<BoundingBoxComponent>(size);
    enemy->addComponent<EnemyTag>();
    enemy->addComponent<Gravity>();

    auto &texture =
        enemy->addComponent<TextureComponent2>(0.05f, true, "Goomba-Idle-Left");

    std::vector<Texture2D> textures;
    textures.push_back(LoadTexture("./assets/Goomba/Goomba-Left-Idle.png"));
    textures.push_back(LoadTexture("./assets/Goomba/Goomba-Left-Moving.png"));

    texture.addTextures("Goomba-Idle-Left", textures);

    textures.clear();
    textures.push_back(LoadTexture("./assets/Goomba/Goomba-Right-Moving.png"));
    textures.push_back(LoadTexture("./assets/Goomba/Goomba-Right-Idle.png"));
    texture.addTextures("Goomba-Idle-Right", textures);

    textures.clear();
    textures.push_back(LoadTexture("./assets/Goomba/Goomba-Die.png"));
    texture.addTextures("Goomba-Die", textures);

    // enemy->getComponent<TextureComponent2>().addTexture(
    //     "Goomba-Die", "./assets/Goomba/Goomba-Die.png");
    //
    // enemy->getComponent<TextureComponent2>().addTexture(
    //     "Goomba-Left-Idle", "./assets/Goomba/Goomba-Left-Idle.png");
    // enemy->getComponent<TextureComponent2>().addTexture(
    //     "Goomba-Right-Idle", "./assets/Goomba/Goomba-Right-Idle.png");
    //
    // enemy->getComponent<TextureComponent2>().addTexture(
    //     "Goomba-Left-Moving", "./assets/Goomba/Goomba-Left-Moving.png");
    // enemy->getComponent<TextureComponent2>().addTexture(
    //     "Goomba-Right-Moving", "./assets/Goomba/Goomba-Right-Moving.png");
    return enemy;
}

Shared<AbstractEntity> EntityFactory::createBlock(string type, Vector2 position) {
  Texture2D texture = TextureManager::getInstance().getTexture(type);
  std::cerr<<"Still good get into createBlock"<<std::endl; 
  Shared<AbstractEntity> block = nullptr;
  if(type == "NormalBlock"){
    block = std::make_shared<NormalBlock>(position);
  }
  else if(type == "BrokenBlock"){
    block = std::make_shared<BrokenBlock>(position);
  }
  else if(type == "HardBlock"){
    block = std::make_shared<HardBlock>(position);
  }
  else if(type == "GroundBlock"){
    block = std::make_shared<GroundBlock>(position);
  }
  else if(type == "QuestionBlock"){
    block = std::make_shared<QuestionBlock>(position);
  }
  return block;
}

Shared<AbstractEntity> EntityFactory::createPipe(Vector2 position, Vector2 size) {
    Shared<AbstractEntity> pipe = std::make_shared<Pipe>(position, size);
    pipe->addComponent<StillObjectTag>();
    return pipe;
}

Shared<AbstractEntity> EntityFactory::createFlag(Vector2 position) {
    Shared<AbstractEntity> flag = std::make_shared<Flag>(position);

    flag->addComponent<StillObjectTag>();
    return flag;
}

Shared<AbstractEntity> EntityFactory::createFlagPole(Vector2 position)
{
  Shared<AbstractEntity> flagPole = std::make_shared<FlagPole>(position);
  return flagPole;
}
