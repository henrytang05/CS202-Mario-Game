#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Character.h"
#include "Entity/Entity.h"
#include "Entity/EntityFactory.h"
#include "Scene.h"

namespace SceneSpace {
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> update() override;
  void draw() override;
  void loadResources() override;
  void start() override;
  bool isFinished();
  void init();

private:
  // std::vector<Shared<Character>> characters;
  std::vector<Shared<Entity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
