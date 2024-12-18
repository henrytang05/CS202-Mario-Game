#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "AbstractEntity.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Map.h"
#include "Scenes/Scene.h"

#include "Entity/EnemySystem.h"

namespace SceneSpace {
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> updateScene(float deltaTime) override;
  void update(float deltaTime);
  void draw() override;
  void loadResources() override;
  bool isFinished();
  void init() override;

private:
  double time;
  Texture2D background;
  MapRenderer mapRenderer;
  Camera2D camera;
  Shared<PlayableEntity> player;
  std::vector<Shared<AbstractEntity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;

  // just a small test

  // TODO: remove this later
private:
  void testEnemyCreated();
  void updateEnemies();
  void drawEnemies();

  std::vector<Shared<AbstractEntity>> enemies;
  EnemyAISystem enemyAISystem;
  EnemyRenderSystem enemyRenderSystem;
  EnemyCollisionSystem enemyCollisionSystem;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
