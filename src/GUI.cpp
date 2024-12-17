#include "GUI.h"

GUI::ImageButton::ImageButton(float x, float y, const char* idelTextureFile, const char* hoverTextureFile)
{
    posX = x;
    posY = y;
    idelTexture = LoadTexture(idelTextureFile);
    hoverTexture = LoadTexture(hoverTextureFile);
}

void GUI::ImageButton::update(Vector2& mousePos, bool& isLeftClick)
{
    Rectangle rect = {posX, posY, (float)idelTexture.width, (float)idelTexture.height};
    buttonState = BTN_IDLE;
    if (CheckCollisionPointRec(mousePos,rect))
    {
	    buttonState = BTN_HOVER;
        if(isLeftClick) buttonState = BTN_PRESSED;
    }
}

void GUI::ImageButton::draw()
{
    if(buttonState == BTN_IDLE) DrawTexture(idelTexture, posX, posY, WHITE);
    else DrawTexture(hoverTexture, posX, posY, WHITE);
}

bool GUI::ImageButton::isPressed()
{
	if (buttonState == BTN_PRESSED) return true;
	return false;
}

double GUI::get_delta_time()
{
    static auto lastTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();

    double delta = std::chrono::duration<double>(currentTime - lastTime).count();
    lastTime = currentTime;

    return delta;
}
