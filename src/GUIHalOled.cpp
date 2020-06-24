#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/TomThumb.h>

#include "GUIHalOled.h"
#include "Free_Fonts.h"


//#include <SPI.h>
//#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

LcdOled::LcdOled(/* args */) {}

LcdOled::~LcdOled() {}


void LcdOled::begin() {

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
}

void LcdOled::update() {
    display.display();
}

void LcdOled::clearDisplay() {
    display.clearDisplay();
}

void LcdOled::drawRect(int posX, int posY, int width, int heigh, int color) {
    display.drawRect(posX, posY, width, heigh, color);
    
    display.drawRect(posX, posY, width, heigh, color);
    delayOled();

}

void LcdOled::drawLine(int posX, int posY, int newX, int newY, int color) {
    display.drawLine(posX, posY, newX, newY, color);

    display.drawLine(posX, posY, newX, newY, color);
    delayOled();
}

void LcdOled::fillRect(int posX, int posY, int width, int heigh, int color) {
    display.fillRect(posX, posY, width, heigh, color);
    delayOled();
}

void LcdOled::fillScreen(int color){
    display.fillScreen(color);
    delayOled();
}

void LcdOled::setTextDatum(int tcDatum){
    //M5.lcd.setTextDatum(tcDatum);
    // TODO: What is used for?
}

void LcdOled::setTextColor(int color){
    display.setTextColor(color);
}

void LcdOled::setTextSize(int size){
    display.setTextSize(size);
}

void LcdOled::setFreeFont(std::string fontName){

    // Using Free_Fonts.h
    
    const GFXfont* font = FF21;

    if (fontName=="FF21") font = FF21;
    if (fontName=="FF22") font = FF22;
    if (fontName=="TT1") font = TT1;

    display.setFont(font);
}

void LcdOled::drawString(std::string textToDraw, int posX, int posY){
    int posXOld;
    int posYOld;
    posXOld = display.getCursorX();
    posYOld = display.getCursorY();
    
    display.setCursor(posX, posY);
    display.print(textToDraw.c_str());
    display.setCursor(posXOld, posYOld);

    delayOled();
}

void LcdOled::println(std::string textToPrint){
    display.println(textToPrint.c_str());
    delayOled();
}

void LcdOled::setBitmapColor(int fColor, int bColor){
    
    // White and black.
    // Two options B-W, W-B

}

int LcdOled::getCursorX() {
    display.getCursorX();
}

int LcdOled::getCursorY() {
    display.getCursorY();
    
}

void LcdOled::setCursor(int posX, int posY) {
    display.setCursor(posX, posY);
}

void LcdOled::pushImage(int x0, int y0, int w, int h, uint8_t  *data, bool bpp8){
    
    display.drawBitmap(x0, y0, data, w, h, COLOR_WHITE);
}


// Private

void LcdOled::delayOled(){
    display.display();
    delay(1);
}


////////////////////////////////////////////////////


BtnOled::BtnOled(int btnNum) {
    _btnNum = btnNum;
}

BtnOled::~BtnOled() {
}

int BtnOled::wasPressed() {

    int btnWasPressed=0;

    /*
    if (_btnNum==0) btnWasPressed = M5.BtnA.wasPressed();
    if (_btnNum==1) btnWasPressed = M5.BtnB.wasPressed();
    if (_btnNum==2) btnWasPressed = M5.BtnC.wasPressed();
    */

    return(btnWasPressed);
    
}

int BtnOled::wasReleased() {

    int btnWasReleased=0;
    /*
    if (_btnNum==0) btnWasReleased = M5.BtnA.wasReleased();
    if (_btnNum==1) btnWasReleased = M5.BtnB.wasReleased();
    if (_btnNum==2) btnWasReleased = M5.BtnC.wasReleased();
    */
    return(btnWasReleased);
}

int BtnOled::pressedFor(int ms) {

    int btnWasPressedFor=0;
    /*
    if (_btnNum==0) btnWasPressedFor = M5.BtnA.pressedFor(ms);
    if (_btnNum==1) btnWasPressedFor = M5.BtnB.pressedFor(ms);
    if (_btnNum==2) btnWasPressedFor = M5.BtnC.pressedFor(ms);
    */
    return(btnWasPressedFor);
}



