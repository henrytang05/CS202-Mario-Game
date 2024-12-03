#ifndef CHARACTER_H
#define CHARACTER_H
#include "pch.h"
#include "globals.h"
#include "Texture.h"
class Character : public TextureCharacter {
public:
    Character() = default;
    Character(std::string filename, int _numFrame);
    virtual ~Character() = default;
    virtual void update();
    virtual void draw();
private:
  enum State {
    STATE_STANDING, 
    STATE_MOVING,
    STATE_JUMPING,
    STATE_DROPPING
  };
  State characterState;
  int frameIndex;
  int delayFrame, delayFrameCounter;
  float gravity;
  float ground;
  Vector2 velocity, position;
};
#endif // CHARACTER_H
