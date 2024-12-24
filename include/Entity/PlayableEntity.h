// #ifndef PLAYABLE_ENTITY_H
// #define PLAYABLE_ENTITY_H

// #include "Entity/States/CharacterStates.h"
// #include "EntityManager.h"
// #include "Interface.h"
// /*
//         const MIN_WALK = 4.453125;
//         const MAX_WALK = 93.75;
//         const MAX_RUN = 153.75;
//         const ACC_WALK = 133.59375;
//         const ACC_RUN = 200.390625;
//         const DEC_REL = 182.8125;
//         const DEC_SKID = 365.625;
//         const MIN_SKID = 33.75;

//         const STOP_FALL = 1575;
//         const WALK_FALL = 1800;
//         const RUN_FALL = 2025;
//         const STOP_FALL_A = 450;
//         const WALK_FALL_A = 421.875;
//         const RUN_FALL_A = 562.5;

//         const MAX_FALL = 270;
// */

// class PlayableEntity : public AbstractEntity, public IMovable {
// private:
//   float fallAcc;
//   bool isDeath, gameOver;
//   Shared<CharacterState> state;

// public:
//   PlayableEntity();
//   PlayableEntity(std::string name);

//   virtual ~PlayableEntity();
//   Vector2 getVelocity() override;
//   void setVelocity(Vector2 newVelocity) override;
//   virtual void handleInput(float deltaTime);
//   bool checkAlive() const;
//   bool checkOver() const;
//   void update(float deltaTime) override;
//   void setToDie();
//   void setToSmall();
//   void setToLarge();
//   void resolveCollision();
//   void collisionRight();
//   void collisionLeft();
//   void collisionAbove();
//   void collisionBelow();
// };
// #endif // PLAYABLE_ENTITY_H
