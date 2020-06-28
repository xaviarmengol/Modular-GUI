#include <Arduino.h>
#include "GUIHal.h"

#include "modGuiDef.h"

GUIHal GUI(128, 64);

void setup() {

    Serial.begin(115200);

    GUI.Lcd.begin();
    setupModGUI(GUI.getW(), GUI.getH());
        
}

void loop() {
    
    screen->Draw(focus);
    GUI.Lcd.update();
}