#include <Arduino.h>

#include "Button.h"
#include "Free_Fonts.h"

#define GRAPHRESOLUTION 30
#define GRAPHSPACE 10

using namespace Codingfield::UI;

/* Please, please, GUI.Tack, use namespaces around your classes! */

Codingfield::UI::Button::Button(Widget* parent) : Widget(parent) {

}

Codingfield::UI::Button::Button(Widget* parent, int32_t* ptrVar, unsigned long* ptrTime) : Widget(parent, ptrVar, ptrTime) {

  // Define the buffer used in the graph
  circBuffer.SetSize(GRAPHRESOLUTION);

}

Codingfield::UI::Button::Button(Widget* parent, Point position, Size size) : Widget(parent, position, size) {

}




void Codingfield::UI::Button::SetBackgroundColor(Color c) {
  backgroundColorUpdated = true;
  this->backgroundColor = c;
}

void Codingfield::UI::Button::SetTextColor(Color c) {
  this->textColor = c;
}

void Codingfield::UI::Button::SetSelected(bool s) {
  if(isSelected != s) {
    wasSelected = isSelected;
    isSelected = s;
  }
}

void Codingfield::UI::Button::SetText(const std::string& t) {
  if(text != t) {
    if(text.empty())
      oldText = t;
    else
      this->oldText = this->text;
    this->text = t;
  }
}

void Codingfield::UI::Button::SetUnit(const std::string& u) {
  if(unit != u) {
    if(unit.empty())
      oldUnit = u;
    else
      this->oldUnit = this->unit;
    this->unit = u;
  }
}

void Codingfield::UI::Button::SetTitle(const std::string& t) {
  if(title != t) {
    if(title.empty())
      oldTitle = t;
    else
      oldTitle = title;

    title = t;

    // If there is no Code ID, get SetTitle
    if (GetCodeId()=="") SetCodeId(t.c_str());
  }
}

void Codingfield::UI::Button::Draw() {

  bool reDrawGraph=false;

  if(IsHidden()){
    return;
  }

  // Save values to graph later

  if (ptrTime!=nullptr) {

    unsigned long newTime = *ptrTime;

    if (oldTime != newTime) {
      circBuffer.push(*ptrVar);
      //circBuffer.println();
      oldTime = newTime;
      reDrawGraph=true;
    }
  }

  if(!IsInZoom()) { 

    DrawNormal();

  } else if (IsInZoom() && ptrTime!=nullptr) {

    if (reDrawGraph) DrawZoomGraph();

  } else DrawNormal();

  isInvalidated = false;
}


void Codingfield::UI::Button::DrawNormal(std::string strText) {

  // Update with registered var if text is empty

  //println("Draw Normal");

  if(ptrVar != nullptr && strText.empty()) {
    SetText(stringFromVarUnit(*ptrVar, unit, isValueBool));
  } else if (!strText.empty()) {
    SetText(strText);
  }

  bool forceUpdate = isInvalidated;

  if(forceUpdate) {
    Serial.println("FORCEUPDATE " + String(GetCodeId()));
  }

  int x = position.x + (size.width/2);
  int yText;
  int yTitle;
  if(title.empty()) {
    yText = position.y + (size.height/2);
  } else {
    yText = position.y + (size.height/3);
    yTitle = position.y + ((size.height/3)*2);
  }

  if(backgroundColorUpdated || forceUpdate) {
    GUI.Lcd.fillRect(position.x, position.y, size.width, size.height, backgroundColor);
    backgroundColorUpdated = false;
    forceUpdate = true;
  }

  if(forceUpdate || (oldText != text)) {
    GUI.Lcd.setTextDatum(MC_DATUM);
    GUI.Lcd.setTextColor(backgroundColor);
    GUI.Lcd.setTextSize(textSize);

    GUI.Lcd.setFreeFont("FF22");
    GUI.Lcd.drawString(oldText.c_str(), x, yText);

    GUI.Lcd.setTextColor(textColor);
    GUI.Lcd.drawString(text.c_str(), x, yText);
    oldText = text;
  }

  if(forceUpdate || (oldTitle != title)) {
    GUI.Lcd.setTextDatum(MC_DATUM);
    GUI.Lcd.setTextColor(backgroundColor);

    GUI.Lcd.setFreeFont("FF21");
    GUI.Lcd.drawString(oldTitle.c_str(), x, yTitle);

    GUI.Lcd.setTextColor(textColor);
    GUI.Lcd.drawString(title.c_str(), x, yTitle);
    oldTitle = title;
  }

  if(forceUpdate || (wasSelected != isSelected)) {
    if(isSelected) {
      GUI.Lcd.drawRect(position.x, position.y, size.width, size.height, RED);
      GUI.Lcd.drawRect(position.x+1, position.y+1, size.width-2, size.height-2, RED);
      GUI.Lcd.drawRect(position.x+2, position.y+2, size.width-4, size.height-4, RED);
    } else {
      GUI.Lcd.drawRect(position.x, position.y, size.width, size.height, backgroundColor);
      GUI.Lcd.drawRect(position.x + 1, position.y + 1, size.width - 2, size.height - 2, backgroundColor);
      GUI.Lcd.drawRect(position.x + 2, position.y + 2, size.width - 4, size.height - 4, backgroundColor);
    }
  }

}


void Codingfield::UI::Button::DrawZoomGraph() {

  println("Draw Zoom Graph");
  
  if (isInvalidated || coldStart) {
    if (coldStart) coldStart=false;
    GUI.Lcd.fillRect(position.x-1, position.y-1, size.width+2, size.height+2, GUI.Lcd.COLOR_BLACK);
  }

  int spaceInterval = GRAPHSPACE;

  // Draw the graph
  GUI.Lcd.fillRect(position.x-1, position.y-1, size.width+2, size.height+2, GUI.Lcd.COLOR_BLACK);

  valueMin = circBuffer.minValue();
  valueMax = circBuffer.maxValue();

  if (abs(scaleMin - valueMin)<20 || abs(scaleMin - valueMin)>40) scaleMin=valueMin - 30;
  if (abs(scaleMax - valueMax)<20 || abs(scaleMax - valueMax)>40) scaleMax=valueMax + 30;

  GUI.Lcd.setFreeFont("TT1");
  GUI.Lcd.setTextColor(GUI.Lcd.COLOR_WHITE);
  GUI.Lcd.setTextColor(GUI.Lcd.COLOR_WHITE);
  GUI.Lcd.drawString(String(scaleMax).c_str(), position.x+10, position.y+10);
  GUI.Lcd.drawString(String(scaleMin).c_str(), position.x+10, size.height + position.y-10);

  int zeroScaled = size.height + position.y - map(0, scaleMin, scaleMax, 0, size.height);
  GUI.Lcd.drawLine(position.x+5, zeroScaled, position.x + size.width -5, zeroScaled, GUI.Lcd.COLOR_WHITE);

  for (int i=0;i<GRAPHRESOLUTION;i++) {

    int value = circBuffer.at(i);
    value = constrain(value, 0, size.height);

    int valueScale = map(value, scaleMin, scaleMax, 0, size.height);

    //GUI.Lcd.drawString(String(value), position.x+10, size.height + position.y-10);

    //int x = position.x + ((GRAPHRESOLUTION-1-i) * spaceInterval) % size.width;
    int x = position.x + (i* spaceInterval) % size.width;
    int y = size.height + position.y - valueScale;

    if (i>0) GUI.Lcd.drawLine(lastX, lastY, x, y, RED);

    lastX = x;
    lastY = y;
  }

  
}


std::string Codingfield::UI::Button::stringFromVarUnit(int32_t val, std::string unitStr, bool isBool) {

  std::string textVal;

  if (isBool) {

    if (val==0) textVal="OFF";
    else textVal="ON";
    
  } else  {
    textVal = String(val).c_str() + unitStr;
  }

  return(textVal);
}
