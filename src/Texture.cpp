#include "Texture.h"
#include "Logger.h"
#include "globals.h"

TextureCharacter::TextureCharacter(std::string filename, int _numFrame) {
    numFrame = _numFrame;
    texture = LoadTexture((filename + ".png").c_str());
    flipTexture = LoadTexture((filename + "-Flip.png").c_str());
    isFlip = 0;
    frameWidth = texture.width/numFrame;
    frameRec = {(float)frameWidth, 0.0f, (float)frameWidth, (float)texture.height};
}
bool TextureCharacter::getIsFlip() {
    return isFlip;
}
void TextureCharacter::updateFlip() {
    isFlip ^= 1;
}
void TextureCharacter::drawTexture(Vector2 position) {
    Rectangle dest = {position.x, position.y, (float)frameWidth * 4.0f, (float)texture.height * 4.0f};
    if(isFlip) {
        DrawTexturePro(flipTexture, frameRec, dest, {0.0f, 0.0f}, 0.0f, WHITE); // Mario x4 size
        //DrawTextureRec(flipTexture, frameRec, position, WHITE);
    }
    else { 
        DrawTexturePro(texture, frameRec, dest, {0.0f, 0.0f}, 0.0f, WHITE); // Mario x4 size
        //DrawTextureRec(texture, frameRec, position, WHITE);
    }
}
void TextureCharacter::updateFrame(int frameIndex) {
    if(isFlip) {
        frameRec.x = float(frameWidth * (numFrame - frameIndex - 1));
    }
    else 
        frameRec.x = float(frameWidth * frameIndex);
}