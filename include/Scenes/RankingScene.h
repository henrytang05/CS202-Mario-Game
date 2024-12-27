#ifndef RANKINGSCENE_H
#define RANKINGSCENE_H

#include "GUI.h"
#include "Scenes/Scene.h"

namespace SceneSpace {
class RankingScene : public Scene {
public:
  RankingScene();
  ~RankingScene();
  Unique<SceneSpace::Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;

private:
  Texture background;
};
} // namespace SceneSpace
#endif // RANKINGSCENE_H
