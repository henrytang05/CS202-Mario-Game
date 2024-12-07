#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "Entity/Entity.h"

class TextureComponent : public Component {
public:
  TextureComponent(std::string filename, int _numFrame);
  virtual ~TextureComponent() = default;
  void drawTexture();
  void updateFrame(int frameIndex);
  void updateFlip();
  void init() override;
  void update() override;

  bool getIsFlip();

private:
  int numFrame;
  int frameWidth;
  bool isFlip;
  Rectangle frameRec;
  Texture2D flipTexture, texture;
};

#endif // TEXTURE_COMPONENT_H
