
#include <string>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class LcdOled {

    private:
        void delayOled();

    public:
        LcdOled(/* args */);
        ~LcdOled();

        void begin();
        void update();
        void clearDisplay();

        void fillRect(int posX, int posY, int width, int heigh, int color);
        void drawRect(int posX, int posY, int width, int heigh, int color);
        void drawLine(int posX, int posY, int newX, int newY, int color);
        void fillScreen(int color);

        void setTextDatum(int tcDatum);
        void setTextColor(int color);
        void setTextSize(int size);
        void setFreeFont(std::string fontName);
        void drawString(std::string textToDraw, int posX, int posY);
        void println(std::string textToPrint);

        int getCursorX();
        int getCursorY();
        void setCursor(int posX, int posY);

        void setBitmapColor(int fColor, int bColor);
        void pushImage(int x0, int y0, int w, int h, uint8_t *data, bool bpp8 = true);

        const int COLOR_BLACK = SSD1306_BLACK; //BLACK;
        const int COLOR_WHITE = SSD1306_WHITE; //WHITE;
        
};

class BtnOled {

    private:
        int _btnNum = 0;
        
    public:
        BtnOled(int btnNum);
        ~BtnOled();

        int wasPressed();
        int wasReleased();
        int pressedFor(int ms);

};

