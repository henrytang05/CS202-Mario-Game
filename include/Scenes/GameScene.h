#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "AbstractEntity.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Map.h"
#include "Scenes/Scene.h"
#include "System/System.h"
#include "Entity/EnemySystem.h"
#include "GUI.h"
namespace SceneSpace {
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  Unique<Scene> updateScene(float deltaTime) override;
  void update(float deltaTime);
  void draw() override;
  void loadResources() override;
  bool isFinished();
  void init() override;

private:
  bool IsMario = isMario;
  double time;
  Texture2D background;
  MapRenderer mapRenderer;
  Camera2D camera;
  Shared<PlayableEntity> player;
  std::vector<Shared<AbstractEntity>> entities;
  Unique<IFactory> entityFactory;
  bool gameOver;
  GUI::ImageButton* GuideButton;
  // TODO: remove this later
private:
  std::vector<Unique<System>> systems;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
