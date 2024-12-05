#include "Entity/Entity.h"

#include "Components/Components.h"
#include "Components/Texture.h"

Entity::Entity() : active(true), name("Unnamed") { init(); }
Entity::Entity(std::string name) : active(true), name(name) {
#ifdef _DEBUG
    Log("log.txt", LogLevel::DEBUG, name + " created\n");
#endif
    init();
}

void Entity::init() { componentBitset.reset(); }

Entity::~Entity() {
#ifdef _DEBUG
    Log("log.txt", LogLevel::DEBUG, name + " destroy\n");
#endif
}

void Entity::update() {
    for (auto &c : components) {
        c->update();
    }
}

void Entity::draw() {
    ASSERT(hasComponent<PositionComponent>());
    ASSERT(hasComponent<CameraComponent>());
    ASSERT(hasComponent<TextureComponent>());
    PositionComponent &positionC = getComponent<PositionComponent>();
    Vector2 position = positionC.getPos();
    CameraComponent &camera = getComponent<CameraComponent>();

    BeginMode2D(camera);
    getComponent<TextureComponent>().drawTexture(position);
    DrawLine(0.0f, ground, screenWidth, ground, BLACK);
    ClearBackground(RAYWHITE);
    EndMode2D();
}

bool Entity::isActive() const { return active; }
void Entity::destroy() { active = false; }
