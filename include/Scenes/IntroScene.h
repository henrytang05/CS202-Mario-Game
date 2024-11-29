#ifndef INTROSCENE_H
#define INTROSCENE_H
namespace SceneSpace {
class Scene;

class IntroScene : public Scene {
public:
  IntroScene();
  ~IntroScene();
  Shared<Scene> update() override;
  void draw() override;
  void acceptInputHandler(InputHandler inputHandler) override;
  void loadResources() override;
  void start() override;
  void pressEnter() override;
private:
  bool changeScreen;
  Texture background;
};
} // namespace SceneSpace
#endif // INTROSCENE_H
