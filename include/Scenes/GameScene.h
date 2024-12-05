#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Texture.h"
#include "Map.h"
namespace SceneSpace {
class Scene;
class GameScene : public Scene {
public:
  GameScene();
  ~GameScene();
  Shared<Scene> update() override;
  void draw() override;
  void acceptInputHandler(InputHandler inputHandler) override;
  void loadResources() override;
  void start() override;
  bool isFinished();
  void pressUp() override;
  void pressNothing() override;
  void pressLeft() override;
  void pressRight() override;
  Vector2 getCameraTarget();
private:
  int frameIndex;
  int frameDelay;
  int frameDelayCounter;
  int gravity;
  float ground;
  Vector2 velocity, position;
  bool gameOver;
  std::vector<Shared<TextureSmallCharacter>> characters;
  TileFactory factory;
  MapRenderer mapRenderer;
};
} // namespace SceneSpace

#endif // GAMESCENE_H
