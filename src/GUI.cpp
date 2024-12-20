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

GUI::Slider::Slider(int x, int y, int width, int height, int knobRadius, float &initialValue, Color sliderColor, Color knobColor) 
    : x(x), y(y), width(width), height(height), knobRadius(knobRadius), 
          value(initialValue), sliderColor(sliderColor), knobColor(knobColor) {}

void GUI::Slider::update(Vector2& mousePos)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mousePos, (Rectangle){(float)x, (float)y, (float)width, (float)height})) {
        value = (mousePos.x - x) / (float)width;
        if (value < 0.0f) value = 0.0f;
        if (value > 1.0f) value = 1.0f;
    }
}

void GUI::Slider::draw()
{
    DrawRectangle(x, y, width, height, sliderColor);
    int knobX = x + (int)(value * width);
    DrawCircle(knobX, y + height / 2, knobRadius, knobColor);
}

float GUI::Slider::getValue()
{
    return value;
}

void GUI::Slider::setValue(float newValue)
{
    if (newValue < 0.0f) newValue = 0.0f;
    if (newValue > 1.0f) newValue = 1.0f;
    value = newValue;
}
