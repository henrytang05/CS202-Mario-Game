#include "Entity/EntityFactory.h"

#include <cstddef>

#include "Components/Components_include.h"
#include "Entity/Mario.h"
#include "EntityManager.h"
#include "pch.h"
#include "raylib.h"

EntityFactory::EntityFactory(EntityManager &EM) : IFactory(EM) {}
//
Weak<AbstractEntity> EntityFactory::createMario() { return initMario(EM); }
Weak<AbstractEntity> EntityFactory::createLuigi() { return initLuigi(EM); }
Weak<AbstractEntity> EntityFactory::createGoomba(Vector2 position, Vector2 size) {
    return initGoomba(EM, position, size);
}

Weak<AbstractEntity> EntityFactory::createEnemy(Vector2 position, Vector2 size) {
    return initGoomba(EM, position, size);
}

Weak<AbstractEntity> EntityFactory::createBlock(std::string type, Vector2 position) {
    Texture2D texture = TextureManager::getInstance().getTexture(type);

    Weak<AbstractEntity> luigi =
        EntityManager::getInstance().createEntity("Luigi") luigi.lock()->addComponent

            std::cerr
        << "Still good get into createBlock" << std::endl;
    Weak<AbstractEntity> block;
    if (type == "NormalBlock") {
        block = std::make_shared<NormalBlock>(position, &EM);
    } else if (type == "BrokenBlock") {
        block = std::make_shared<BrokenBlock>(position, &EM);
    } else if (type == "HardBlock") {
        block = std::make_shared<HardBlock>(position, &EM);
    } else if (type == "GroundBlock") {
        block = std::make_shared<GroundBlock>(position, &EM);
    } else if (type == "QuestionBlock") {
        block = std::make_shared<QuestionBlock>(position, &EM);
    } else {
        throw std::runtime_error("Block type not found");
    }
    return block;
}

Weak<AbstractEntity> EntityFactory::createPipe(Vector2 position, Vector2 size) {
    //   Weak<Pipe>(position, size);
    //   pipe->addComponent<StillObjectTag>();
    //   return pipe;
    // }
    //
    // Weak<AbstractEntity> EntityFactory::createFlag(Vector2 position) {
    //   Weak<AbstractEntity>(position);
    //
    //   flag->addComponent<StillObjectTag>();
    //   return flag;
    // }
    //
    // Weak<AbstractEntity> EntityFactory::createFlagPole(Vector2 position) {
    //   Weak<AbstractEntity>(position);
    //   return flagPole;
    Shared<Pipe> pipe = std::make_shared<Pipe>(position, size, &EM);
    return pipe;
}

Weak<AbstractEntity> EntityFactory::createFlag(Vector2 position) {
    Shared<Flag> flag = std::make_shared<Flag>(position, &EM);
    return flag;
}

Weak<AbstractEntity> EntityFactory::createFlagPole(Vector2 position) {
    Shared<FlagPole> flagPole = std::make_shared<FlagPole>(position, &EM);
    return flagPole;
}
