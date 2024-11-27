#ifndef TEXTURE_H
#define TEXTURE_H
#include "pch.h"
class TextureSmallCharacter {
private:    
    int numFrame;
    int frameWidth;
    bool isFlip;
    Rectangle frameRec;
    Texture2D flipTexture, texture;
public:
    TextureSmallCharacter(){};
    TextureSmallCharacter(const char *filename);
    void drawTexture(Vector2 position);
    void updateFrame(int frameIndex);
    void updateFlip();

    bool getIsFlip();
};
#endif // TEXTURE_H