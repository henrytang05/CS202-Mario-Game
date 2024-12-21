#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Components/BlockTrigger.h"

Unique <IFactory> _entityFactory;

NormalBlock::NormalBlock(Vector2 position): AbstractEntity("NormalBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("NormalBlock"));
}

void NormalBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void NormalBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

BrokenBlock::BrokenBlock(Vector2 position): AbstractEntity("BrokenBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<BlockTriggerComponent>();
    addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("BrokenBlock"));
}

void BrokenBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void BrokenBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

HardBlock::HardBlock(Vector2 position): AbstractEntity("HardBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("HardBlock"));
}

void HardBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void HardBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

GroundBlock::GroundBlock(Vector2 position): AbstractEntity("GroundBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("GroundBlock"));
}

void GroundBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void GroundBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

QuestionBlock::QuestionBlock(Vector2 position): AbstractEntity("QuestionBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("QuestionBlock"));
    
    //items.push_back(_entityFactory->createCoin({position.x, position.y - 16.0f}));
    
}

void QuestionBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
    // for(auto &entity : items)
    //     entity->draw();
}

void QuestionBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

Pipe::Pipe(Vector2 position, Vector2 size): AbstractEntity("Pipe") {
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    std::cerr<<"create pipe"<<std::endl;
}

void Pipe::draw() {
    // ASSERT(hasComponent<TextureComponent>());
    // getComponent<TextureComponent>().drawTexture("Normal");
}

void Pipe::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

//
Flag::Flag(Vector2 position): AbstractEntity("Flag") {
    Vector2 size = {16, 16};
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Flag") );

    std::cerr<<"create flag"<<std::endl;
}

void Flag::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void Flag::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

FlagPole::FlagPole(Vector2 position): AbstractEntity("FlagPole") {
    Vector2 size = {16, 16};
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("FlagPole") );

    std::cerr<<"create flagpole"<<std::endl;
}

void FlagPole::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void FlagPole::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}