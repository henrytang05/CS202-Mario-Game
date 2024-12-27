#ifndef GUIDESCENE_H
#define GUIDESCENE_H
#include "GUI.h"
#include "Scenes/Scene.h"
#include "EntityManager.h"
#include "Entity/EntityFactory.h"

namespace SceneSpace {
class GuideScene : public Scene {
public:
  GuideScene();
  ~GuideScene();
  Unique<SceneSpace::Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;
  void update(float deltaTime);
private:
  Texture background;
  // Shared<PlayableEntity> player;
  // std::vector<Shared<AbstractEntity>> entities;
  // Unique<IFactory> entityFactory;
};
} // namespace SceneSpace
#endif // GUIDESCENE_HH
