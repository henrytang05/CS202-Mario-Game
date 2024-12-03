#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Texture.h"
namespace SceneSpace {
class Scene;
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> update() override;
  void draw() override;
  void loadResources() override;
  void start() override;
  bool isFinished();
private:
  enum State {
    STATE_STANDING, 
    STATE_MOVING,
    STATE_JUMPING,
    STATE_DROPPING
  };
  State characterState;
  int frameIndex;
  int frameDelay;
  int frameDelayCounter;
  float gravity;
  float ground;
  Vector2 velocity, position;
  bool gameOver;
  std::vector<Shared<TextureSmallCharacter>> characters;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
