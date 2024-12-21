#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H
#include "Components/Component.h"
#include "raylib.h"
#include <unordered_map>

struct Animation {
  Animation(float frameDelay = 0.1f, bool isLooping = true);
  float frameDelay;
  float elapsedTime;
  bool isLooping;
  int currentFrame;
  std::vector<Texture2D> frames;

  Texture2D &operator[](int index);
};

class TextureComponent : public Component {
public:
  TextureComponent();
  virtual ~TextureComponent() = default;
  virtual void addTexture(std::string state, std::string filename);
  virtual void addTexture(std::string state, Texture2D texture);
  virtual void addTexture(std::string state, std::vector<Texture2D> textures,
                          float frameDelay = 0.1f, bool isLooping = true);
  virtual void addAnimation(std::string state, Animation animation);
  void changeState(std::string state);
  void drawTexture(std::string state);
  void init() override;
  void update(float deltaTime) override;

public:
  std::string state;
  std::string lastState;
  std::unordered_map<std::string, Animation> textures;
};

#endif // TEXTURE_COMPONENT_H
