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

  _statusSpace = GUI.Lcd.TEXT_MARGIN;

  if(IsHidden()) return;
  bool wasInvalidated = isInvalidated;
  Bar::Draw();

  std::string wifiDescription = "?";
  std::string oldWifiDescription = "";

  if(wasInvalidated || (wifiStatus != oldWifiStatus)) {
    const uint8_t* wifibmp = image_data_wifi0;

    switch(wifiStatus) {
      case WifiStatuses::Weak: 
        wifibmp = image_data_wifi1; 
        wifiDescription = "W";
        break;
      case WifiStatuses::Medium: 
        wifibmp = image_data_wifi2; 
        wifiDescription = "M";
        break;
      case WifiStatuses::Full: 
        wifibmp = image_data_wifi3; 
        wifiDescription = "F";
        break;

      default:
      case WifiStatuses::No_signal:
        wifibmp = image_data_wifi0;
        wifiDescription = "X";
        break;
    }


    if (GUI.getW()>300) {
      int imageSize = 25;
      GUI.Lcd.setBitmapColor(GUI.Lcd.COLOR_BLACK, color);
      GUI.Lcd.pushImage(GUI.getW()-imageSize, 0, imageSize, imageSize, const_cast<uint8_t*>(wifibmp), false);
    } else {

      GUI.Lcd.setTextColor(color);
      GUI.Lcd.drawString(oldWifiDescription, getPosEndX() - 10, _statusSpace);

      GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
      GUI.Lcd.drawString(wifiDescription, getPosEndX() - 10, _statusSpace);
    }

    oldWifiStatus = wifiStatus;
    oldWifiDescription = wifiDescription;
  }

  if(wasInvalidated || (oldDateTime != dateTime)) {

    if (GUI.getW()>300) {
      GUI.Lcd.setTextDatum(TC_DATUM);

      GUI.Lcd.setTextColor(color);
      GUI.Lcd.drawString(oldDateTime.c_str(), size.width/2, _statusSpace);

      GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
      GUI.Lcd.drawString(dateTime.c_str(), size.width/2, _statusSpace);

      oldDateTime = dateTime;
    } else {
      // GUI.Lcd.drawString("Date", getPosMidX(), _statusSpace);
    }


  }

  if(wasInvalidated || (oldUptime != uptime)) {
    GUI.Lcd.setTextDatum(TL_DATUM);

    GUI.Lcd.setTextColor(color);
    String s = String("UP:") + String(oldUptime) + String("min");
    GUI.Lcd.drawString(s.c_str(), position.x + 1 , _statusSpace);

    GUI.Lcd.setTextColor(GUI.Lcd.COLOR_BLACK);
    s = String("UP:") + String(uptime) + String("min");
    GUI.Lcd.drawString(s.c_str(), position.x + 1, _statusSpace);

    oldUptime = uptime;
  }
  isInvalidated = false;
}
