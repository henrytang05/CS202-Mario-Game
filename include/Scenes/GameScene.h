#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "AbstractEntity.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Map.h"
#include "Scenes/Scene.h"

namespace SceneSpace {
class GameScene : public Scene, public AbstractEntity {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> updateScene() override;
  void update() override;
  void draw() override;
  void loadResources() override;
  bool isFinished();
  void init() override;

private:
  Texture2D background;
  MapRenderer mapRenderer;
  Camera2D camera;
  Shared<PlayableEntity> player;
  std::vector<Shared<AbstractEntity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
