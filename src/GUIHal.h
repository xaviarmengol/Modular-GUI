#pragma once

#include "GUIHalM5.h"
#include "GUIHalOled.h"

#include "BtnSerial.h"

class GUIHal {

    private:
        int _w;
        int _h;

    public:
        GUIHal(int w, int h);
        ~GUIHal();

        // Public GUI Hal objects

        LcdOled Lcd = LcdOled(_w, _h);

        BtnSerial BtnA = BtnSerial(0);
        BtnSerial BtnB = BtnSerial(1);
        BtnSerial BtnC = BtnSerial(2);

        int getW();
        int getH();

};

extern GUIHal GUI;