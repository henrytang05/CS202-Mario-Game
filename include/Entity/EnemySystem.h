// #ifndef ENEMY_SYSTEM_H
// #define ENEMY_SYSTEM_H
//
// #include "EntityManager.h"
// #include "Components/Collision.h"
// #include "Components/EnemyComponents.h"
// #include "Components/Texture.h"
// #include "globals.h"
// #include <functional>
// using EnemyAISystem = std::function<void(
//     EnemyPosition &position, EnemyVelocity &velocity, EnemySize &size)>;
//
// using EnemyRenderSystem = std::function<void(EnemyPosition &, EnemyVelocity
// &,
//                                              TextureComponent &, int dt)>;
//
// using EnemyCollisionSystem =
//     std::function<void(CollisionComponent &, EnemyPosition &, EnemyVelocity
//     &,
//                        TextureComponent &, AbstractEntity &)>;
//
// EnemyAISystem createEnemyAISystem();
// EnemyRenderSystem createEnemyRenderSystem();
// EnemyCollisionSystem createEnemyCollisionSystem();
//
// // Define the Enemy AI system lambda
// #endif // ENEMY_SYSTEM_H
