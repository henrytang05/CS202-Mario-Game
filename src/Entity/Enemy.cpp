#include "Entity/Enemy.h"

#include "AbstractEntity.h"
#include "Components/Collision.h"
#include "Components/EnemyComponents.h"
#include "Components/Gravity.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "globals.h"
#include "raylib.h"

Enemy::Enemy(std::string name) : AbstractEntity(name) {
    // Initialize enemy
}
void Enemy::update(float deltatime) {
    for (auto &component : components) {
        component->update(deltatime);
    }

    handleCollision();
}

void Enemy::handleCollision() {
    CollisionComponent &collision = getComponent<CollisionComponent>();
    auto above = collision.getAbove();
    auto below = collision.getBelow();
    auto left = collision.getLeft();
    auto right = collision.getRight();

    Vector2 v = {-ENEMY_SPEED, 0};

    auto &trans = getComponent<TransformComponent>();
    float g = getComponent<Gravity>();
    if (left && !left->hasComponent<EnemyTag>())
        v = {ENEMY_SPEED, trans.getVelocity().y};
    else if (right && !right->hasComponent<EnemyTag>())
        v = {ENEMY_SPEED, trans.getVelocity().y};

    if (!below) {
        if (getComponent<PositionComponent>().getY() > screenHeight) {
            destroy();
            getComponent<TextureComponent2>().changeState("Goomba-Die");
        }
    }
    trans.setVelocity(v);
    if (above)
        if (above->hasComponent<PlayerTag>()) {
            destroy();
            getComponent<TextureComponent2>().changeState("Goomba-Die");
        }
}

void Enemy::draw() {
    // for (auto &component : components) {
    //   component->draw();
    // }
}
