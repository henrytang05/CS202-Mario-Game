#include "AABB.h"

AABB::AABB(Vector2 position, Vector2 size) {
    box = (Rectangle){position.x, position.y, size.x, size.y};
}
bool AABB::checkCollision(const AABB &other) const {
    return (box.x <= other.box.x + other.box.width
            && box.x + box.width >= other.box.x 
            && box.y <= other.box.y + other.box.height
            && box.y + box.height >= other.box.y);
}
void AABB::setPosition(Vector2 position) {
    box.x = position.x;
    box.y = position.y;
}
Vector2 AABB::getPosition() const {
    return (Vector2){box.x, box.y};
}