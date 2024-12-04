#ifndef CHARACTER_H
#define CHARACTER_H
#include "pch.h"
#include "globals.h"
#include "Texture.h"
class CharacterState;
class Character : public TextureCharacter {
public:
    Character() = default;
    Character(std::string filename, int _numFrame);
    virtual ~Character();
    virtual void update();
    virtual void setVelocity(Vector2 newVelocity);
    virtual Vector2 getVelocity();
    virtual bool isOnTheGround();
    virtual void draw();
private:
  CharacterState *stateCharacter;
  float ground;
  Vector2 velocity, position;
};
#endif // CHARACTER_H
