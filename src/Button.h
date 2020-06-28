#pragma once

#include <Widget.h>
#include <CircularQueue.h>
#include <vector>

//#include "GUIHal.h"


// Necessary to deal with ButtonInfoBar / StatusBar handlers
#include <ButtonInfoBar.h>
#include <StatusBar.h>

namespace Codingfield {
  namespace UI {
    class Button : public Widget {
    public:
      Button(Widget* parent);
      Button(Widget* parent, int32_t* ptrVar, unsigned long* ptrTime=nullptr); // NEW
      Button(Widget* parent, Point position, Size size);

      void SetBackgroundColor(Color c);
      void SetTextColor(Color c);
      virtual void SetSelected(bool s) override;
      void SetText(const std::string& t);
      void SetTitle(const std::string& t);
      void SetUnit(const std::string& t);
      void Draw() override;
      void DrawNormal(std::string strText="");
      void DrawZoomGraph();

      void setIsBinary (bool isBool) { isValueBool = isBool; inputMin=0; inputMax=1;}

      // Config inputs constrains

      void setMinValue (int min){ inputMin = min; }
      void setMaxValue (int max){ inputMax = max; }

    protected:
      Color backgroundColor = GUI.Lcd.COLOR_BLACK;
      bool backgroundColorUpdated = true;
      Color textColor = GUI.Lcd.COLOR_BLACK;
      std::string text="";
      std::string oldText;
      std::string title;
      std::string oldTitle;
  
      // Display

      std::string unit; // NEW
      std::string oldUnit;

      bool isValueBool = false;
      std::string stringFromVarUnit(int32_t strVal, std::string unitStr, bool isBool = false);

      // Display mode
      
      // TODO: Implement modes system
      //std::vector<String> modes = {};

      int lastX=0;
      int lastY=0;
      bool coldStart=true;

      bool wasSelected = false;

      // Input specific

      int inputMin = INT_MIN;
      int inputMax = INT_MAX;

      
      // Display graph
      
      CircularQueue circBuffer;
      unsigned long oldTime;
      int scaleMin;
      int scaleMax;

      int valueMin;
      int valueMax;

    };
  }
}
