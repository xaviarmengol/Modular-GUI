#include "GUIHalM5.h"
#include "Free_Fonts.h"

LcdM5::LcdM5(/* args */) {}

LcdM5::~LcdM5() {}

void LcdM5::begin(){
    M5.begin();
}

void LcdM5::update() {
    M5.update();
}

void LcdM5::clearDisplay() {
    M5.Lcd.clearDisplay();
}

void LcdM5::drawRect(int posX, int posY, int width, int heigh, int color) {
    M5.lcd.drawRect(posX, posY, width, heigh, color);
}

void LcdM5::drawLine(int posX, int posY, int newX, int newY, int color) {
    M5.lcd.drawLine(posX, posY, newX, newY, color);
}

void LcdM5::fillRect(int posX, int posY, int width, int heigh, int color) {
    M5.lcd.fillRect(posX, posY, width, heigh, color);
}

void LcdM5::fillScreen(int color){
    M5.lcd.fillScreen(color);
}

void LcdM5::setTextDatum(int tcDatum){
    M5.lcd.setTextDatum(tcDatum);
}

void LcdM5::setTextColor(int color){
    M5.lcd.setTextColor(color);
}

void LcdM5::setTextSize(int size){
    M5.lcd.setTextSize(size);
}

void LcdM5::setFreeFont(std::string fontName){

    // Using Free_Fonts.h

    const GFXfont* font = FF21;

    if (fontName=="FF21") font = FF21;
    if (fontName=="FF22") font = FF22;
    if (fontName=="TT1") font = TT1;

    M5.lcd.setFreeFont(font);

}

void LcdM5::drawString(std::string textToDraw, int posX, int posY){
    M5.lcd.drawString(textToDraw.c_str(), posX, posY);
}

void LcdM5::println(std::string textToPrint){
    M5.lcd.println(textToPrint.c_str());
}

void LcdM5::setBitmapColor(int fColor, int bColor){
    M5.lcd.setBitmapColor(fColor, bColor);
    
}

int LcdM5::getCursorX() {
    M5.lcd.getCursorX();
}

int LcdM5::getCursorY() {
    M5.lcd.getCursorY();
}

void LcdM5::setCursor(int posX, int posY) {
    M5.lcd.setCursor(posX, posY);
}

void LcdM5::pushImage(int x0, int y0, int w, int h, uint8_t  *data, bool bpp8){
    M5.lcd.pushImage(x0, y0, w, h, data, bpp8);
}


////////////////////////////////////////////////////


BtnM5::BtnM5(int btnNum) {
    _btnNum = btnNum;
}

BtnM5::~BtnM5() {
}

int BtnM5::wasPressed() {
    int btnWasPressed=0;
    if (_btnNum==0) btnWasPressed = M5.BtnA.wasPressed();
    if (_btnNum==1) btnWasPressed = M5.BtnB.wasPressed();
    if (_btnNum==2) btnWasPressed = M5.BtnC.wasPressed();

    return(btnWasPressed);
}

int BtnM5::wasReleased() {
    int btnWasReleased=0;
    if (_btnNum==0) btnWasReleased = M5.BtnA.wasReleased();
    if (_btnNum==1) btnWasReleased = M5.BtnB.wasReleased();
    if (_btnNum==2) btnWasReleased = M5.BtnC.wasReleased();

    return(btnWasReleased);
}

int BtnM5::pressedFor(int ms) {
    int btnWasPressedFor=0;
    if (_btnNum==0) btnWasPressedFor = M5.BtnA.pressedFor(ms);
    if (_btnNum==1) btnWasPressedFor = M5.BtnB.pressedFor(ms);
    if (_btnNum==2) btnWasPressedFor = M5.BtnC.pressedFor(ms);

    return(btnWasPressedFor);
}
