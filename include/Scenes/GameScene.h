#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Entity/EntityFactory.h"
#include "EntityManager.h"
#include "Map.h"
#include "Scenes/Scene.h"
#include "ScoreManager.h"
#include "System/System.h"
namespace SceneSpace {
class GameScene : public Scene {
public:
  GameScene();
  GameScene(const std::string &_nameScene, const std::string &_level);
  GameScene(bool resume);
  GameScene &operator=(GameScene &&other) noexcept;
  ~GameScene();
  Unique<Scene> updateScene(float deltaTime) override;
  void update(float deltaTime);
  void draw() override;
  void loadResources() override;
  bool isFinished();
  void init() override;
  void save();
  void load();

private:
  std::string nameScene, level;
  bool IsMario = isMario;
  double time;
  Texture2D background;
  MapRenderer mapRenderer;
  Camera2D camera;
  EntityManager *EM;
  Weak<AbstractEntity> player;
  bool gameOver;
  Unique<IFactory> entityFactory;
  std::vector<Weak<AbstractEntity>> entities;

private:
  static int lives;
  static inline std::string savePath = "data/GameScene/";
  std::vector<Shared<System>> systems;
  std::vector<Weak<IUpdatableSystem>> update_systems;
  std::vector<Weak<IDrawableSystem>> draw_systems;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
