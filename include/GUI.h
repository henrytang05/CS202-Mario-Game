#pragma once
#include <chrono>

namespace GUI{
    // IMAGEBUTTON
    class ImageButton{
        enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED };
    private:
		short unsigned buttonState = 0;
		Texture idelTexture;
		Texture hoverTexture;
        Vector2 position;
        float posX, posY;
    public:
        ImageButton(float x, float y, const char* idelTextureFile, const char* hoverTextureFile);
        void update(Vector2& mousePos, bool& isLeftClick);
		void draw();
		bool isPressed();
    };

    double get_delta_time();
}
