#ifndef CHARACTER_H
#define CHARACTER_H
#include "AABB.h"
#include "Texture.h"
#include "globals.h"
#include "pch.h"
class CharacterState;
class Character : public TextureCharacter, public AABB {
public:
  Character() = default;
  Character(std::string filename, int _numFrame, Vector2 _position,
            Vector2 _size);
  virtual ~Character();
  virtual void update();
  virtual void setVelocity(Vector2 newVelocity);
  virtual Vector2 getVelocity();
  virtual Vector2 getPosition();
  virtual bool isOnTheGround();
  virtual void draw();

private:
  CharacterState *stateCharacter;
  AABB ground = AABB((Vector2){0.0f, 784.0f}, (Vector2){screenWidth, 0.0f});
  AABB boundLeft = AABB((Vector2){0.0f, 0.0f}, Vector2{0.0f, screenHeight});
  AABB boundRight =
      AABB((Vector2){screenWidth, 0.0f}, Vector2{0.0f, screenHeight});
  Vector2 velocity, position;
  Vector2 size;
};
#endif // CHARACTER_H
