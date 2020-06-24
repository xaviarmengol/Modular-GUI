#pragma once

#include "GUIHalM5.h"
#include "GUIHalOled.h"


class GUIHal {

    private:
    /* data */

    public:
        GUIHal(/* args */);
        ~GUIHal();

        // Public GUI Hal objects

        LcdOled Lcd;

        BtnM5 BtnA = BtnM5(0);
        BtnM5 BtnB = BtnM5(1);
        BtnM5 BtnC = BtnM5(2);

};
