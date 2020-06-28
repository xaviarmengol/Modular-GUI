
#include <M5Stack.h>

class LcdM5 {
    private:
        int _w;
        int _h;
        
    public:
        LcdM5(int w, int h);
        ~LcdM5();

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
        void pushImage(int x0, int y0, int w, int h, uint8_t  *data, bool bpp8 = true);

        // Configuration

        const int COLOR_BLACK = BLACK;
        const int COLOR_WHITE = WHITE;
        const int COLOR_RED = RED;
        
        const int WIDGET_PADDING = 5;
        const int TEXT_MARGIN = 5;
        const int BAR_HEIGHT = 25;

        const int GRAPH_RESOLUTION = 30;
        const int GRAPH_SPACE = 10;

        const int GRAPH_MARGIN = 10;
        const int BUTTON_LINE = 5;

        
};

class BtnM5 {

    private:
        int _btnNum = 0;
        
    public:
        BtnM5(int btnNum);
        ~BtnM5();

        int wasPressed();
        int wasReleased();
        int pressedFor(int ms);

};

