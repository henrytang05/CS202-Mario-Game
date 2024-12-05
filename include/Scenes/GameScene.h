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
  std::vector<Shared<Character>> characters;
  TileFactory tileFactory;
  MapRenderer mapRenderer;
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
