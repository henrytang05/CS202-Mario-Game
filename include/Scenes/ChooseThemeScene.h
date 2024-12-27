#ifndef CHOOSETHEMESCENE_H
#define CHOOSETHEMESCENE_H
#include "GUI.h"
#include "Scenes/Scene.h"
namespace SceneSpace {

class ChooseThemeScene : public Scene {
public:
  ChooseThemeScene();
  ~ChooseThemeScene();
  Unique<Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;

private:
  Texture background;
  GUI::ImageButton *Air;
  GUI::ImageButton *Water;
  GUI::ImageButton *Fire;
};
} // namespace SceneSpace
#endif // CHOOSETHEMESCENE_H
