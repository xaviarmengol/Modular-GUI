#include "StatusBar.h"

using namespace Codingfield::UI;

extern const uint8_t image_data_wifi0[];
extern const uint8_t image_data_wifi1[];
extern const uint8_t image_data_wifi2[];
extern const uint8_t image_data_wifi3[];

void StatusBar::SetWifiStatus(const StatusBar::WifiStatuses status) {
  if(wifiStatus != status) {
    oldWifiStatus = wifiStatus;
    wifiStatus = status;
  }
}

void StatusBar::SetUptime(const uint32_t t) {
  if(uptime != t) {
    oldUptime = uptime;
    uptime = t;
  }
}

void StatusBar::SetDateTime(const std::string& t) {
  if(dateTime != t) {
    oldDateTime = dateTime;
    dateTime = t;
  }
}

void StatusBar::Draw() {
  if(IsHidden()) return;
  bool wasInvalidated = isInvalidated;
  Bar::Draw();

  if(wasInvalidated || (wifiStatus != oldWifiStatus)) {
    const uint8_t* wifibmp = image_data_wifi0;
    switch(wifiStatus) {
      case WifiStatuses::Weak: wifibmp = image_data_wifi1; break;
      case WifiStatuses::Medium: wifibmp = image_data_wifi2; break;
      case WifiStatuses::Full: wifibmp = image_data_wifi3; break;
      default:
      case WifiStatuses::No_signal:
        wifibmp = image_data_wifi0;
        break;
    }

    GUI.Lcd.setBitmapColor(GUI.Lcd.COLOR_BLACK, color);
    GUI.Lcd.pushImage(295, 0, 25, 25, const_cast<uint8_t*>(wifibmp), false);

    oldWifiStatus = wifiStatus;
  }

  if(wasInvalidated || (oldDateTime != dateTime)) {
    GUI.Lcd.setTextDatum(TC_DATUM);

    GUI.Lcd.setTextColor(color);
    GUI.Lcd.drawString(oldDateTime.c_str(), 160, 5);

    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
    GUI.Lcd.drawString(dateTime.c_str(), 160, 5);

    oldDateTime = dateTime;
  }

  if(wasInvalidated || (oldUptime != uptime)) {
    GUI.Lcd.setTextDatum(TL_DATUM);

    GUI.Lcd.setTextColor(color);
    String s = String("UP:") + String(oldUptime) + String("min");
    GUI.Lcd.drawString(s.c_str(), 1, 5);

    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
    s = String("UP:") + String(uptime) + String("min");
    GUI.Lcd.drawString(s.c_str(), 1, 5);

    oldUptime = uptime;
  }
  isInvalidated = false;
}
