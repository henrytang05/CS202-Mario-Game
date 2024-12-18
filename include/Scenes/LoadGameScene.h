#ifndef LOADGAMESCENE_H
#define LOADGAMESCENE_H
#include "GUI.h"
#include "Scenes/Scene.h"

namespace SceneSpace {
class LoadGameScene : public Scene {
public:
  LoadGameScene();
  ~LoadGameScene();
  Shared<SceneSpace::Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;

private:
  Texture background;
  GUI::ImageButton* QuitButton;
};
} // namespace SceneSpace
#endif // LOADGAMESCENE_H
