#ifndef CHARACTER_H
#define CHARACTER_H

#include "Texture.h"
#include "globals.h"
class CharacterState;
class Character : public TextureCharacter {
public:
  Character() = default;
  Character(std::string filename, int _numFrame, Vector2 _size);
  virtual ~Character();
  virtual void update();
  virtual void setVelocity(Vector2 newVelocity);
  virtual Vector2 getVelocity();
  virtual bool isOnTheGround();
  virtual void draw();

private:
  Camera2D camera = {0};
  CharacterState *stateCharacter;
  Vector2 velocity, position;
  Vector2 size;
};
#endif // CHARACTER_H
