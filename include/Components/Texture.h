#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H
#include "Components/Component.h"
#include "raylib.h"

class TextureComponent : public Component {
public:
  TextureComponent();
  virtual ~TextureComponent() = default;
  virtual void addTexture(std::string state, std::string filename);
  virtual void addTexture(std::string state, Texture2D texture);
  void drawTexture(std::string state);
  void init() override;
  void update(float deltaTime) override;

public:
  std::map<std::string, Texture2D> textures;
};

struct Animation : public Component {
  Animation(float frameDelay, bool isLooping, std::string state);

  void addAnimation(std::string state, std::vector<Texture2D> textures);
  void changeState(std::string state);

  float frameDelay;  // Delay between frames in seconds
  float elapsedTime; // Accumulated time since last frame change
  bool isLooping;
  int currentFrame;
  std::string animationState; // Current animation state
  std::string lastAnimationState;

  std::unordered_map<std::string, std::vector<Texture2D>> animations;
};

#endif // TEXTURE_COMPONENT_H
