#include "ButtonInfoBar.h"

using namespace Codingfield::UI;

void ButtonInfoBar::SetButtonAText(const std::string& t) {
  if(btnAText != t) {
    oldBtnAText = btnAText;
    btnAText = t;
  }
}

void ButtonInfoBar::SetButtonBText(const std::string& t) {
  if(btnBText != t) {
    oldBtnBText = btnBText;
    btnBText = t;
  }
}

void ButtonInfoBar::SetButtonCText(const std::string& t) {
  if(btnCText != t) {
    oldBtnCText = btnCText;
    btnCText = t;
  }
}

void ButtonInfoBar::Draw() {

  int barSpace = GUI.Lcd.TEXT_MARGIN;

  if(IsHidden()) return;
  bool oldIsInvalidated = isInvalidated;
  Bar::Draw();

  if(oldIsInvalidated || (oldBtnAText != btnAText)) {
    GUI.Lcd.setTextDatum(TC_DATUM);
    GUI.Lcd.setTextColor(color);
    GUI.Lcd.drawString(oldBtnAText.c_str(), (size.width/6), position.y + barSpace);
    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
    GUI.Lcd.drawString(btnAText.c_str(), (size.width/6), position.y + barSpace);

    oldBtnAText = btnAText;
  }

  if(oldIsInvalidated || (oldBtnBText != btnBText)) {
    GUI.Lcd.setTextDatum(TC_DATUM);
    GUI.Lcd.setTextColor(color);
    GUI.Lcd.drawString(oldBtnBText.c_str(), size.width/2, position.y + barSpace, true);
    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
    GUI.Lcd.drawString(btnBText.c_str(), size.width/2, position.y + barSpace, true);

    oldBtnBText = btnBText;
  }

  if(oldIsInvalidated || (oldBtnCText != btnCText)) {
    GUI.Lcd.setTextDatum(TC_DATUM);
    GUI.Lcd.setTextColor(color);
    GUI.Lcd.drawString(oldBtnCText.c_str(), ((size.width/3)*2) + (size.width/6), position.y + barSpace);
    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
    GUI.Lcd.drawString(btnCText.c_str(), ((size.width/3)*2) + (size.width/6), position.y + barSpace);
    
    oldBtnCText = btnCText;
  }
  isInvalidated = false;
}
