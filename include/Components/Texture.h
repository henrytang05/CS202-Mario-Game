#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H
#include "Components/Component.h"

class TextureComponent : public Component {
public:
  TextureComponent();
  virtual ~TextureComponent() = default;
  void addTexture(std::string state, std::string filename);
  void addTexture(std::string state, Texture2D texture);
  void drawTexture(std::string state);
  void init() override;
  void update() override;
private:
  std::map<std::string, Texture2D> textures;
};

#endif // TEXTURE_COMPONENT_H
