#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"

GameObject::GameObject(std::string name): AbstractEntity(name){}

Block::Block(Texture2D texture, Vector2 position)
: GameObject("Block") {

    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", texture);
}

Block::~Block() {
    // Destructor implementation (if needed)
}

void Block::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}