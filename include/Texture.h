#ifndef TEXTURE_H
#define TEXTURE_H

class TextureCharacter {
private:
  int numFrame;
  int frameWidth;
  bool isFlip;
  Rectangle frameRec;
  Texture2D flipTexture, texture;

public:
  TextureCharacter() = default;
  virtual ~TextureCharacter() = default;
  TextureCharacter(std::string filename, int _numFrame);
  void drawTexture(Vector2 position);
  void updateFrame(int frameIndex);
  void updateFlip();

  bool getIsFlip();
};
#endif // TEXTURE_H
