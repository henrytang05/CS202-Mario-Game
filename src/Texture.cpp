#include "Texture.h"
#include "Logger.h"
#include "globals.h"

TextureSmallCharacter::TextureSmallCharacter(const char *filename) {
    char tmp1[20];
    strcpy(tmp1, filename);
    strcat(tmp1, ".png");
    texture = LoadTexture(tmp1);
    numFrame = 11;
    isFlip = 0;
    frameWidth = texture.width/numFrame;
    frameRec = {(float)frameWidth, 0.0f, (float)frameWidth, (float)texture.height};
    char tmp2[20];
    strcpy(tmp2, filename);
    strcat(tmp2, "-Flip.png");
    flipTexture = LoadTexture(tmp2);
}
bool TextureSmallCharacter::getIsFlip() {
    return isFlip;
}
void TextureSmallCharacter::updateFlip() {
    isFlip ^= 1;
}
void TextureSmallCharacter::drawTexture(Vector2 position) {
    if(isFlip) {
        DrawTextureRec(flipTexture, frameRec, position, WHITE);
    }
    else DrawTextureRec(texture, frameRec, position, WHITE);
}
void TextureSmallCharacter::updateFrame(int frameIndex) {
    if(isFlip) {
        frameRec.x = float(frameWidth * (numFrame - frameIndex - 1));
    }
    else 
        frameRec.x = float(frameWidth * frameIndex);
}