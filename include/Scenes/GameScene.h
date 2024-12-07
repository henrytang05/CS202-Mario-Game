#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Components/Camera.h"
#include "Entity/EntityFactory.h"
#include "Interface.h"
#include "Scene.h"

namespace SceneSpace {
class GameScene : public Scene, public AbstractEntity {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> updateScene() override;
  void draw() override;
  void loadResources() override;
  void start() override;
  bool isFinished();
  void init();

private:
  // std::vector<Shared<Character>> characters;
  CameraComponent &camera;
  std::vector<Shared<Entity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
