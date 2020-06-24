#include "UpDownButton.h"
#include "Free_Fonts.h"
using namespace Codingfield::UI;

UpDownButton::UpDownButton(Widget* parent) : Button(parent) {
  isEditable = true;
}

UpDownButton::UpDownButton(Widget* parent, int* ptrVar, bool confirmValue) : Button(parent, ptrVar) {
  isEditable = true;
  confirmToChange = confirmValue;

}

void UpDownButton::Draw() {
  if(IsHidden()) return;

  bool wasInvalidated = isInvalidated;

  if (IsInZoom()) Button::DrawNormal(stringFromVarUnit(currentValue, unit, isValueBool));
  else Button::DrawNormal();
  
  isInvalidated = false;

  if(wasInvalidated) {
    if(controlsEnabled) {
      GUI.Lcd.setTextDatum(MC_DATUM);
      GUI.Lcd.setTextColor(textColor);
      GUI.Lcd.setTextSize(textSize);
      GUI.Lcd.drawString("-", position.x + (size.width/6), position.y + (size.height/2));
      GUI.Lcd.drawString("+", position.x + (size.width - (size.width/6)), position.y + (size.height/2));

    }
  }
}


void UpDownButton::EnableControls()  {
  controlsEnabled = true;

  // Get the current value
  currentValue = *ptrVar;
  oldValue = *ptrVar;
}

void UpDownButton::DisableControls() {
  controlsEnabled = false;
}

void UpDownButton::OnButtonAPressed() {
  if(upCallback != nullptr) {
    downCallback(this);
  } else {
    currentValue--;
    currentValue = constrain(currentValue, inputMin, inputMax);
    if (!confirmToChange) *ptrVar = currentValue;
    Invalidate();
  }
}

void UpDownButton::OnButtonBPressed() {
  if(applyCallback != nullptr) {
    applyCallback(this);
  } else {
    *ptrVar = currentValue;
    SetText(stringFromVarUnit(*ptrVar, unit, isValueBool));
    Invalidate();
  }
}

void UpDownButton::OnButtonBLongPush() {
  if(cancelCallback != nullptr) {
    cancelCallback(this);
  } else {
    *ptrVar = oldValue;
    SetText(stringFromVarUnit(*ptrVar, unit, isValueBool));
    Invalidate();
  }
}

void UpDownButton::OnButtonCPressed() {
  if(upCallback != nullptr) {
    upCallback(this);
  } else {
    currentValue++;
    currentValue = constrain(currentValue, inputMin, inputMax);
    if (!confirmToChange) *ptrVar = currentValue;
    Invalidate();
  }
}

void UpDownButton::SetUpCallback(std::function<bool (UpDownButton* widget)> callback) {
  upCallback = callback;
}

void UpDownButton::SetDownCallback(std::function<bool (UpDownButton* widget)> callback) {
  downCallback = callback;
}

void UpDownButton::SetApplyCallback(std::function<bool (UpDownButton* widget)> callback) {
  applyCallback = callback;
}

void UpDownButton::SetCancelCallback(std::function<bool (UpDownButton* widget)> callback) {
  cancelCallback = callback;
}
