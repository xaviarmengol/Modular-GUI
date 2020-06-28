// GUI Includes

#include <Screen.h>
#include <ButtonInfoBar.h>
#include <StatusBar.h>
#include <Button.h>
#include <WidgetMosaicComp.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <AppScreen.h>
#include <UpDownButton.h>
#include <Logscreen.h>

#include "GUIHal.h"


// Global application variables in GUI

unsigned long seconds = 0;
unsigned long tenMiliSeconds=0;
int32_t uptimeMinutes=0;

int32_t inpRot = 0;
int32_t inpElev = 0;
int32_t lidarDist = 0;


// Objects declarations

using namespace Codingfield::UI;
AppScreen* screen;
StatusBar* topBar;
ButtonInfoBar* bottomBar;

WidgetMosaicComp* mosaic;

Codingfield::UI::UpDownButton* setRot;
Codingfield::UI::UpDownButton* setElev;

Widget* focus;

// Objects initialitzation

void setupModGUI(int w, int h) {


    // Instanciate and configure all widgets
    topBar = new StatusBar();
    topBar->SetUptime(0);
    topBar->SetWifiStatus(StatusBar::WifiStatuses::No_signal);

    bottomBar = new ButtonInfoBar();
    bottomBar->SetButtonAText("<");
    bottomBar->SetButtonBText("SELECT");
    bottomBar->SetButtonCText(">");

    mosaic = new WidgetMosaicComp(nullptr, 2, 1, topBar, bottomBar, &lidarDist);
    mosaic->SetBackgroundColor(GUI.Lcd.COLOR_BLACK);
    mosaic->SetTextColor(GUI.Lcd.COLOR_WHITE);
    mosaic->SetTitle("Lidar dist");
    mosaic->SetTextSize(1);

    screen = new AppScreen(Size(w, h), GUI.Lcd.COLOR_BLACK, topBar, bottomBar, mosaic);

    // Mosaic   2 lines

    setRot = new Codingfield::UI::UpDownButton(mosaic, &inpRot, false); 
    setRot->SetBackgroundColor(GUI.Lcd.COLOR_WHITE);
    setRot->SetTextColor(GUI.Lcd.COLOR_BLACK);
    setRot->SetUnit(" o");
    setRot->SetTitle("Rot");


    setElev = new Codingfield::UI::UpDownButton(mosaic, &inpElev, false); 
    setElev->SetBackgroundColor(GUI.Lcd.COLOR_WHITE);
    setElev->SetTextColor(GUI.Lcd.COLOR_BLACK);
    setElev->SetUnit(" o");
    setElev->SetTitle("Elev");


    // Give the focus to the main screen
    focus = mosaic;

    // Draw the screen and all its children
    screen->Draw();
}