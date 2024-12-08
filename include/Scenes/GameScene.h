#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "AbstractEntity.h"
#include "Components/Camera.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Scene.h"

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
  // std::vector<Shared<Character>> characters;
  CameraComponent &camera;
  Shared<PlayableEntity> player;
  std::vector<Shared<AbstractEntity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
