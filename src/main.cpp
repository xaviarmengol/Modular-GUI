#include <Arduino.h>
#include "GUIHal.h"

GUIHal GUI;

void setup() {

    GUI.Lcd.begin();
    
    GUI.Lcd.drawLine(0,0,50,50,GUI.Lcd.COLOR_WHITE);

}

void loop() {
    // GUI.Lcd.update();
}