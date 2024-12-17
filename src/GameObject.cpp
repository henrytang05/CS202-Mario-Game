#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"

NormalBlock::NormalBlock(Texture2D texture, Vector2 position): AbstractEntity("NormalBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", texture);
}

void NormalBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void NormalBlock::update() {
    // Implementation of the update function
}

BrokenBlock::BrokenBlock(Texture2D texture, Vector2 position): AbstractEntity("BrokenBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", texture);
    std::cerr<<"create broken block"<<std::endl;
}

void BrokenBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void BrokenBlock::update() {
    // Implementation of the update function
}

HardBlock::HardBlock(Texture2D texture, Vector2 position): AbstractEntity("HardBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", texture);
    std::cerr<<"create hard block"<<std::endl;
}

void HardBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void HardBlock::update() {
    // Implementation of the update function
}

GroundBlock::GroundBlock(Texture2D texture, Vector2 position): AbstractEntity("GroundBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", texture);
    std::cerr<<"create ground block"<<std::endl;
}

void GroundBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void GroundBlock::update() {
    // Implementation of the update function
}

QuestionBlock::QuestionBlock(Texture2D texture, Vector2 position): AbstractEntity("QuestionBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", texture);
    std::cerr<<"create question block"<<std::endl;
}

void QuestionBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void QuestionBlock::update() {
    // Implementation of the update function
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

void Pipe::update() {
    // Implementation of the update function
}

//
Flag::Flag(Vector2 position): AbstractEntity("Flag") {
    Vector2 position_fix = {position.x, position.y};
    Vector2 size = {2, 128};
    addComponent<PositionComponent>(position_fix);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", LoadTexture("Map/Flag.png"));

    std::cerr<<"create flag"<<std::endl;
}

void Flag::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void Flag::update() {
    // Implementation of the update function
}