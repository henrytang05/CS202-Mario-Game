// #include "Entity/PlayableEntity.h"
// #include "Components/Components_include.h"
// #include "Components/SoundComponent.h"
// #include "Entity/States/CharacterStates.h"
// using namespace std;

// PlayableEntity::PlayableEntity(std::string name)
//     : AbstractEntity(name), fallAcc(GRAVITY_DEC), isDeath(false),
//       gameOver(false),
//       state(std::make_shared<DroppingState>("SMALL", "RIGHT")) {
//   initEntity();
//   addComponent<PlayerTag>();
// }

// PlayableEntity::~PlayableEntity() { state = nullptr; }
// PlayableEntity::PlayableEntity()
//     : fallAcc(GRAVITY_DEC), isDeath(false), gameOver(false),
//       state(std::make_shared<DroppingState>("SMALL", "RIGHT")) {
//   addComponent<PlayerTag>();
// }
// void PlayableEntity::setVelocity(Vector2 newVelocity) {
//   ASSERT(hasComponent<TransformComponent>());
//   getComponent<TransformComponent>().setVelocity(newVelocity);
// }

// Vector2 PlayableEntity::getVelocity() {
//   ASSERT(hasComponent<TransformComponent>());
//   return getComponent<TransformComponent>().getVelocity();
// }
// bool PlayableEntity::checkAlive() const { return !isDeath; }
//
// <<<<<<< HEAD
// bool PlayableEntity::checkOver() const {
//   return gameOver;
// }
// void PlayableEntity::setToDie() {
//   state = make_shared<DeathState>("SMALL", state->getFacing());
//   getComponent<MarioSoundComponent>().PlayMarioDieEffect();
// }
// void PlayableEntity::setToSmall() {
//   state->setSizeState("SMALL");
//   getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 20.0f});
//   Vector2 position = getComponent<PositionComponent>().getPosition();
//   getComponent<PositionComponent>().setPosition((Vector2){position.x,
//   position.y + 8.0f});
// }
// void PlayableEntity::setToLarge() {
//   state->setSizeState("LARGE");
//   getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 28.0f});
//   Vector2 position = getComponent<PositionComponent>().getPosition();
//   getComponent<PositionComponent>().setPosition((Vector2){position.x,
//   position.y - 8.0f});
// }
// void PlayableEntity::collisionRight() {
//   auto right = getComponent<CollisionComponent>().getRight();
//   if(right.lock() != nullptr) {
//     if(right.lock()->hasComponent<EnemyTag>()) {
//       if(state->getSize() == "SMALL")
//         setToDie();
//       else {
//         setToSmall();
//       }
//     }
//   }
// }
// void PlayableEntity::collisionLeft() {
//   auto left = getComponent<CollisionComponent>().getLeft();
//   if(left.lock() != nullptr) {
//     if(left.lock()->hasComponent<EnemyTag>()) {
//       if(state->getSize() == "SMALL")
//         setToDie();
//       else {
//         setToSmall();
//       }
//     }
//   }
// }
// void PlayableEntity::collisionAbove() {
//   auto above = getComponent<CollisionComponent>().getAbove();
//   if(above.lock()) {
//     if(above.lock()->name == "BrokenBlock") {
//       if(state->getSize() == "SMALL") {
//         above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new
//         TriggerBrokenBlockWhenHitBySmall(above.lock()->getComponent<PositionComponent>().getPosition()));
//         getComponent<MarioSoundComponent>().PlayBumpEffect();
//       }
//       else{
//         above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new
//         TriggerBrokenBlockWhenHitByLarge(above.lock()->getComponent<PositionComponent>().getPosition()));
//         getComponent<MarioSoundComponent>().PlayBreakBlockEffect();
//       }
//     }
//     if(above.lock()->name == "QuestionBlock")
//     {
//       above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new
//       TriggerQuestionBlock(above.lock()->getComponent<PositionComponent>().getPosition()));
//       getComponent<MarioSoundComponent>().PlayBumpEffect();
//     }
//     if(above.lock()->hasComponent<EnemyTag>()) {
//       if(state->getSize() == "SMALL")
//         setToDie();
//       else {
//         setToSmall();
//       }
//     }
//     // if(above.lock()->name == "Coin") {
//     //   above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new
//     TriggerCoin(above.lock()->getComponent<PositionComponent>().getPosition()));
//     //   getComponent<MarioSoundComponent>().PlayCoinEffect();
//     // }
//   }
// }
// void PlayableEntity::collisionBelow() {
//   auto below = getComponent<CollisionComponent>().getBelow();
//   if(below.lock() != nullptr) {
//     if(below.lock()->hasComponent<EnemyTag>()) {
//       if(below.lock()->name == "Piranha") {
//         if(state->getSize() == "SMALL")
//           setToDie();
//         else {
//           setToSmall();
//         }
//       }
//       if(below.lock()->hasComponent<CollisionComponent>())
//         below.lock()->getComponent<CollisionComponent>().setAbove(Shared<PlayableEntity>(this));
//     }
//   }
// }
// void PlayableEntity::resolveCollision() {
//   collisionAbove();
//   collisionBelow();
//   collisionLeft();
//   collisionRight();
// }
// void PlayableEntity::update(float deltaTime) {
//   if(getComponent<PositionComponent>().getY() > 1.2f * screenHeight) {
//     setToDie();
//   }
//   if(state->getState() == "DEATH") {
//     isDeath = true;
//     getComponent<TextureComponent>().changeState(state->getCurrentState());
//     getComponent<TransformComponent>().setVelocity({0.0f, -200.0f});
//     getComponent<TransformComponent>().update(deltaTime);
//     if(getComponent<PositionComponent>().getPosition().y < 0.0f) {
//       gameOver = true;
//     }
//     return;
//   }
//   handleInput(deltaTime);
//   getComponent<CollisionComponent>().reset();
//   for (auto &component : components) {
//     component->update(deltaTime);
//   }
// =======
// // bool PlayableEntity::checkOver() const { return gameOver; }
// // void PlayableEntity::setToDie() {
// //   state = make_shared<DeathState>("SMALL", state->getFacing());
// //   getComponent<MarioSoundComponent>().PlayMarioDieEffect();
// // }
// // void PlayableEntity::setToSmall() {
// //   state->setSizeState("SMALL");
// //   getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 20.0f});
// //   Vector2 position = getComponent<PositionComponent>().getPosition();
// //   getComponent<PositionComponent>().setPosition(
// //       (Vector2){position.x, position.y + 8.0f});
// // }
// // void PlayableEntity::setToLarge() {
// //   state->setSizeState("LARGE");
// //   getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 28.0f});
// //   Vector2 position = getComponent<PositionComponent>().getPosition();
// //   getComponent<PositionComponent>().setPosition(
// //       (Vector2){position.x, position.y - 8.0f});
// // }
// // void PlayableEntity::collisionRight() {
// //   auto right = getComponent<CollisionComponent>().getRight();
// //   if (right.lock() != nullptr) {
// //     if (right.lock()->hasComponent<EnemyTag>()) {
// //       if (state->getSize() == "SMALL")
// //         setToDie();
// //       else {
// //         setToSmall();
// //       }
// //     }
// //   }
// // }
// // void PlayableEntity::collisionLeft() {
// //   auto left = getComponent<CollisionComponent>().getLeft();
// //   if (left.lock() != nullptr) {
// //     if (left.lock()->hasComponent<EnemyTag>()) {
// //       if (state->getSize() == "SMALL")
// //         setToDie();
// //       else {
// //         setToSmall();
// //       }
// //     }
// //   }
// // }
// // // TODO:  fix this later, dont depend on block name
// // void PlayableEntity::collisionAbove() {
// //   auto above = getComponent<CollisionComponent>().getAbove();
// //   if (above.lock()) {
// //     if (above.lock()->getName() == "BrokenBlock") {
// //       if (state->getSize() == "SMALL") {
// //         above.lock()->getComponent<BlockTriggerComponent>().setTrigger(
// //             new TriggerBrokenBlockWhenHitBySmall(
// // above.lock()->getComponent<PositionComponent>().getPosition()));
// //         getComponent<MarioSoundComponent>().PlayBumpEffect();
// //       } else {
// //         above.lock()->getComponent<BlockTriggerComponent>().setTrigger(
// //             new TriggerBrokenBlockWhenHitByLarge(
// // above.lock()->getComponent<PositionComponent>().getPosition()));
// //         getComponent<MarioSoundComponent>().PlayBreakBlockEffect();
// //       }
// //     }
// //     if (above.lock()->getName() == "QuestionBlock") {
// //       above.lock()->getComponent<BlockTriggerComponent>().setTrigger(
// //           new TriggerQuestionBlock(
// // above.lock()->getComponent<PositionComponent>().getPosition()));
// //       getComponent<MarioSoundComponent>().PlayBumpEffect();
// //     }
// //     if (above.lock()->hasComponent<EnemyTag>()) {
// //       if (state->getSize() == "SMALL")
// //         setToDie();
// //       else {
// //         setToSmall();
// //       }
// //     }
// //   }
// // }
// // void PlayableEntity::collisionBelow() {
// //   auto below = getComponent<CollisionComponent>().getBelow();
// //   if (below.lock() != nullptr) {
// //     if (below.lock()->hasComponent<EnemyTag>()) {
// //       if (below.lock()->getName() == "Piranha") {
// //         if (state->getSize() == "SMALL")
// //           setToDie();
// //         else {
// //           setToSmall();
// //         }
// //       }
// //       if (below.lock()->hasComponent<CollisionComponent>())
// //         below.lock()->getComponent<CollisionComponent>().setAbove(
// //             Shared<PlayableEntity>(this));
// //     }
// //   }
// // }
// // void PlayableEntity::resolveCollision() {
// //   collisionAbove();
// //   collisionBelow();
// //   collisionLeft();
// //   collisionRight();
// // }
// // void PlayableEntity::update(float deltaTime) {
// //   if (getComponent<PositionComponent>().y > 1.2f * screenHeight) {
// //     setToDie();
// //   }
// //   if (state->getState() == "DEATH") {
// //     isDeath = true;
// // getComponent<TextureComponent>().changeState(state->getCurrentState());
// //     getComponent<TransformComponent>().setVelocity({0.0f, -200.0f});
// >>>>>>> Huy
//
// //     if (hasComponent<CollisionComponent>())
// //       removeComponent<CollisionComponent>();
//
// //     if (getComponent<PositionComponent>().getPosition().y < 0.0f) {
// //       gameOver = true;
// //     }
// //     return;
// //   }
// //   handleInput(deltaTime);
// //   getComponent<CollisionComponent>().reset();
//
// //   // resolve collision
// //   resolveCollision();
// // }
