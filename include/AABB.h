#ifndef AABB_H
#define AABB_H
#include "pch.h"
#include "globals.h"
class AABB {
private:
    Rectangle box;
public:
    AABB() = default;
    virtual ~AABB() = default;
    AABB(Vector2 position, Vector2 size);
    bool checkCollision(const AABB &other) const;
    void setPosition(Vector2 position);
    Vector2 getPosition() const;
};
#endif // AABB_H
