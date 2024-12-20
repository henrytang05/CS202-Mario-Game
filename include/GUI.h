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
    
    class Slider{
    private:
        int x, y;
        int width, height;   
        int knobRadius;    
        float value;           
        Color sliderColor;   
        Color knobColor;  
    public:
        Slider(int x, int y, int width, int height, int knobRadius, 
           float &initialValue, Color sliderColor, Color knobColor);
        void update(Vector2& mousePos);
        void draw();
        float getValue();
        void setValue(float newValue);
    };
}
