#include "Components/Position.h"

#include "globals.h"

PositionComponent::PositionComponent(Entity *e) : Component(e), position({0, 0}) {
    init();
}

void PositionComponent::init() {
    name = "PositionComponent";
#ifdef _DEBUG
    Log("log.txt", LogLevel::INFO, name + " created");
#endif
}

void PositionComponent::setPos(Vector2 pos) { position = pos; }
Vector2 PositionComponent::getPos() const { return position; }
float PositionComponent::getX() const { return position.x; }
float PositionComponent::getY() const { return position.y; }

void PositionComponent::setX(float x) { position.x = x; }
void PositionComponent::setY(float y) { position.y = y; }

Vector2 operator+(const Vector2 &v1, const Vector2 &v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}
