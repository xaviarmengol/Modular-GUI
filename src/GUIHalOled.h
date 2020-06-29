
// 128 x 64

#include <string>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class LcdOled {

    private:

        void delayOled();
        int fromColorToBW(int color);
        int _w;
        int _h;

        Adafruit_SSD1306 display;

    public:
        LcdOled(int w, int h);
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
        void drawString(std::string textToDraw, int posX, int posY, bool centered=false);
        void println(std::string textToPrint);

        int getCursorX();
        int getCursorY();
        void setCursor(int posX, int posY);

        void setBitmapColor(int fColor, int bColor);
        void pushImage(int x0, int y0, int w, int h, uint8_t *data, bool bpp8 = true);

        // Configuration

        const int COLOR_BLACK = SSD1306_BLACK; //BLACK;
        const int COLOR_WHITE = SSD1306_WHITE; //WHITE;
        const int COLOR_RED = SSD1306_BLACK;
        
        const int WIDGET_PADDING = 2;
        const int TEXT_MARGIN = 2;
        const int BAR_HEIGHT = 10;

        const int GRAPH_RESOLUTION = 24;
        const int GRAPH_SPACE = 5;

        const int GRAPH_MARGIN = 4;
        const int BUTTON_LINE = 2;

        const bool BIG_SELECTOR = false;
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

