#ifndef SCENE_H
#define SCENE_H

namespace SceneSpace {

enum Type : uint8_t { INTRO = 0, GAME };

class Scene {
public:
  virtual ~Scene();
  virtual Shared<Scene> updateScene() = 0;
  virtual void draw() = 0;
  virtual void loadResources() = 0;
  virtual void start() = 0;
  // virtual bool isFinished() = 0;

protected:
};
} // namespace SceneSpace

#endif // SCENE_H
