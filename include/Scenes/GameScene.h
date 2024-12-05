#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Character.h"
#include"Map.h"
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
  Shared<Character> player;
  TileFactory tileFactory;
  MapRenderer mapRenderer;
  Camera2D camera = {0};
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
