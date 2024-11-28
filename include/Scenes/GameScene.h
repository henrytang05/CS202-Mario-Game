#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.h"
#include "Texture.h"
namespace SceneSpace {
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  void Update() override;
  bool isFinished();

private:
  int frameIndex;
  int frameDelay;
  int frameDelayCounter;
  int gravity;
  float ground;
  Vector2 velocity, position;
  bool gameOver;
  std::vector<Shared<TextureSmallCharacter>> characters;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
