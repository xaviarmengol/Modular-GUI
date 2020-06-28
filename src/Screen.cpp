#include "Screen.h"
#include "Free_Fonts.h"

using namespace Codingfield::UI;

void Screen::Draw() {

  GUI.Lcd.setFreeFont("FF21");
  GUI.Lcd.setTextSize(1);

  if(IsHidden()) return;

  if(isInvalidated)
    GUI.Lcd.fillScreen(color);

  for(Widget* w : children)
    w->Draw();

  isInvalidated = false;
    
}
