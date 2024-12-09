#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Character.h"
#include "Map.h"
namespace SceneSpace {
class GameScene : public Scene, public AbstractEntity {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> updateScene() override;
  void update() override;
  void draw() override;
  void loadResources() override;
  void start() override;
  bool isFinished();
  void init();

private:
  Shared<Character> player;
  TileFactory tileFactory;
  MapRenderer mapRenderer;
  Camera2D camera = {0};
  // std::vector<Shared<Character>> characters;
  CameraComponent &camera;
  Shared<PlayableEntity> player;
  std::vector<Shared<AbstractEntity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
