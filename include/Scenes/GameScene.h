#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.h"

namespace SceneSpace {
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  void Update() override;
  bool isFinished();

private:
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
