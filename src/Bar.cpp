#include "Bar.h"

using namespace Codingfield::UI;

void Bar::Draw() {
  if(IsHidden()) return;
  if(isInvalidated)
    GUI.Lcd.fillRect(position.x, position.y, size.width, size.height, GUI.Lcd.COLOR_WHITE);

  isInvalidated = false;
}
