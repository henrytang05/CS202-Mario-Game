#ifndef GUIDESCENE_HH
#define GUIDESCENE_HH
#include "GUI.h"
#include "Scenes/Scene.h"
#include "AbstractEntity.h"
#include "Entity/PlayableEntity.h"
#include "Entity/EntityFactory.h"

namespace SceneSpace {
class GuideScene : public Scene {
public:
  GuideScene();
  ~GuideScene();
  Shared<SceneSpace::Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;
  void update(float deltaTime);
private:
  Texture background;
  GUI::ImageButton* QuitButton;
  // Shared<PlayableEntity> player;
  // std::vector<Shared<AbstractEntity>> entities;
  // Unique<IFactory> entityFactory;
};
} // namespace SceneSpace
#endif // GUIDESCENE_HH
