#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.h"
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  void Update() override;
  bool isFinished() override;

private:
  bool gameOver;
};

#endif // GAMESCENE_H
