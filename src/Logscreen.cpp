#include "Logscreen.h"
#include "Free_Fonts.h"

using namespace Codingfield::UI;

/* Please, please, GUI.Tack, use namespaces around your classes! */

int lcdWidth = 320;

Codingfield::UI::Logscreen::Logscreen(Widget* parent) : Button(parent) {

}

Codingfield::UI::Logscreen::Logscreen(Widget* parent, int32_t* ptrVar, String* ptrTextLine) : Button(parent, ptrVar, nullptr) {
  this->ptrTextLine = ptrTextLine;
}

Codingfield::UI::Logscreen::Logscreen(Widget* parent, Point position, Size size) : Button(parent, position, size) {

}

void Codingfield::UI::Logscreen::Draw() {
  if(IsHidden()){
    return;
  }

  if(!IsInZoom()) {

    // TODO: Draw a GUI.Lcd.COLOR_BLACK rectagle to remove all text.
    //if (_oldIsInZoom) GUI.Lcd.fillRect(0, position.y-1, lcdWidth, size.height+2, GUI.Lcd.COLOR_BLACK);

    Button::DrawNormal();
  }
  else if (ptrTextLine!=nullptr) DrawZoom();
  else DrawNormal();

  _oldIsInZoom = IsInZoom();
  isInvalidated = false;
}


void Codingfield::UI::Logscreen::DrawZoom() {

  if (!_oldIsInZoom || GUI.Lcd.getCursorY() > (position.y + size.height - 5) ) {
    GUI.Lcd.fillRect(0, position.y-1, lcdWidth, size.height+2, GUI.Lcd.COLOR_BLACK);
    GUI.Lcd.setCursor(0, position.y+10);
  }

  if (ptrTextLine != nullptr && oldTextLine != *ptrTextLine) {  
    
    GUI.Lcd.setFreeFont("TT1");
    GUI.Lcd.setTextSize(1);
    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_WHITE);
    GUI.lcd.println((*ptrTextLine).c_str());
    oldTextLine=*ptrTextLine;
  }

}

