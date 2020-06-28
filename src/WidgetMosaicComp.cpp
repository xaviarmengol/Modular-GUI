#include "WidgetMosaicComp.h"
#include "GUIHal.h"
#include "Size.h"
#include "Point.h"

using namespace Codingfield::UI;


WidgetMosaicComp::WidgetMosaicComp(Widget* parent, Point position, Size size, int32_t nbColumns, int32_t nbRows) : Button(parent, position, size),
                                                                                                           nbColumns {nbColumns},
                                                                                                           nbRows {nbRows} {

  SetMosaic(true);                                                                                                             
}

WidgetMosaicComp::WidgetMosaicComp(int32_t nbColumns, int32_t nbRows) : WidgetMosaicComp(nullptr, Point(), Size(), nbColumns, nbRows) {

}

// NEW Comp

WidgetMosaicComp::WidgetMosaicComp(Widget* parent, int32_t nbColumns, int32_t nbRows, StatusBar* topBar, ButtonInfoBar* bottomBar, int32_t* ptrVar) : Button(parent, ptrVar) {

    this->nbRows = nbRows;
    this->nbColumns = nbColumns;
    this->bottomBar = bottomBar;
    this->topBar = topBar;

    _guiW = GUI.getW();
    _guiH = GUI.getH();


    SetMosaic(true);

}


void WidgetMosaicComp::Draw() {

  if(IsHidden()){
      return;
  }

  // Going out of ZOOM

  if (oldIsInZoom && !IsInZoom()) {

    Point centerPosition;
    centerPosition.y = 0 + ((topBar != nullptr) ? topBar->GetSize().height : 0) + border;
    centerPosition.x = 0 + border;

    Size centerSize;
    centerSize.height = _guiH - (((bottomBar != nullptr) ? bottomBar->GetSize().height : 0) + ((topBar != nullptr) ? topBar->GetSize().height : 0) + border);
    centerSize.width = _guiW;

  }

  oldIsInZoom = IsInZoom();
    
  if(!IsInZoom()) DrawNormal();

  else {

    DrawZoom();

  }

  isInvalidated = false;
}


void WidgetMosaicComp::DrawZoom() {

    if(IsHidden()) return;

    //println("Draw Zoom Mosaic");

    if(isInvalidated) {
        GUI.Lcd.fillRect(position.x, position.y, size.width, size.height, GUI.Lcd.COLOR_BLACK);
    }

    for(Widget* w : children) {

      w->Draw();

    }

    isInvalidated = false;

    oldIsActiveMosaic = IsMosaicActive();

}



void WidgetMosaicComp::AddChild(Widget* widget) {
  
  Widget::AddChild(widget);

  border = GUI.Lcd.WIDGET_PADDING;

  Size widgetSize;
  Point pos; 

  //println("Add Childs Inside a Mosaic");

  // Add childs with the right position and size

  Point centerPosition;
  centerPosition.y = 0 + ((topBar != nullptr) ? topBar->GetSize().height : 0) + border;
  centerPosition.x = 0 + border;

  Size centerSize;
  centerSize.height = _guiH - (((bottomBar != nullptr) ? bottomBar->GetSize().height : 0) + ((topBar != nullptr) ? topBar->GetSize().height : 0) + GUI.Lcd.WIDGET_PADDING);
  centerSize.width = _guiW;

  widgetSize = ComputeWidgetSize(centerSize, nbColumns, nbRows);
  pos = centerPosition;


  widget->SetSize(widgetSize);

  int32_t position = ((children.size()-1) % (nbRows*nbColumns));
  widget->SetPosition(ComputeWidgetPosition(widgetSize, pos, position));
  Invalidate();
  //widget->println();
}

const Widget* WidgetMosaicComp::GetSelected() const {
  return selectedWidget;
}


// TODO: Factorize this method

void WidgetMosaicComp::ZoomOnSelected(bool enabled) {

  bool oldValue = IsZoomOnSelected();



  if(selectedWidget != nullptr && enabled) {

    //println("Activating Zoom");

    for(auto* w : children)
      w->Hide();
    
    SetZoomOnSelected(true);

    Size widgetSize = ComputeWidgetSize(size,1,1);
    selectedWidget->SetSize(widgetSize);
    selectedWidget->SetPosition(ComputeWidgetPosition(widgetSize, this->position, 0));
    selectedWidget->Show();
    selectedWidget->Invalidate();

    
    if(selectedWidget->IsEditable()) {
      selectedWidget->EnableControls();
    }
  }  else {
    //println("Activating NO Zoom");

    SetZoomOnSelected(false);

    for(auto index = 0; index < children.size(); index++) {
      Widget* widget = children.at(index);
      Size widgetSize = ComputeWidgetSize();
      widget->SetSize(widgetSize);
      widget->SetPosition(ComputeWidgetPosition(widgetSize, this->position, index));
      widget->Show();
      if(selectedWidget->IsEditable()) {
        selectedWidget->DisableControls();
      }
    }
  }

  if(selectedWidget != nullptr && oldValue != IsZoomOnSelected()) {
    
    if (zoomOnSelectedCallback != nullptr) {
      zoomOnSelectedCallback(selectedWidget, IsZoomOnSelected());
    } else {

      if(IsZoomOnSelected()) {

            if(!selectedWidget->IsEditable() && !selectedWidget->IsMosaic()){
                bottomBar->SetButtonAText("");
                bottomBar->SetButtonBText("BACK");
                bottomBar->SetButtonCText("");
            } else if (selectedWidget->IsEditable()){
                bottomBar->SetButtonAText("-");
                bottomBar->SetButtonBText("APPLY/CANC");
                bottomBar->SetButtonCText("+");
            } else {
                bottomBar->SetButtonAText("<");
                bottomBar->SetButtonBText("SEL/BACK");
                bottomBar->SetButtonCText(">");
            }

      } else {
            bottomBar->SetButtonAText("<");
            bottomBar->SetButtonBText("SEL/BACK");
            bottomBar->SetButtonCText(">");
      }
    }
    Invalidate();
  }


}



void WidgetMosaicComp::OnButtonAPressed() {

  if (!IsInZoom() && parent != nullptr) {

    // Managed by upper level if exist

  } else {
    
    if(IsZoomOnSelected())
      return selectedWidget->OnButtonAPressed();

    else {
      children[indexSelected]->SetSelected(false);

      if(indexSelected > 0)
        indexSelected--;
      else {
          indexSelected = children.size()-1;
      }

      children[indexSelected]->SetSelected(true);
      selectedWidget = children[indexSelected];     
    }
  }
}


void WidgetMosaicComp::OnButtonBPressed() {

  if (!IsInZoom()) {
    
    SetInZoom(true);
    Invalidate();

  } else {

    if(selectedWidget == nullptr) return;

    if(IsZoomOnSelected()) {

      if (!selectedWidget->IsMosaic()) ZoomOnSelected(false);
      selectedWidget->OnButtonBPressed();

    } else { 

      if (selectedWidget->IsMosaic() && IsMosaicActive()) {
        SetMosaicActive(false);
        selectedWidget->SetMosaicActive(true);
      }

      ZoomOnSelected(true);
    }

  }
}


void WidgetMosaicComp::OnButtonBLongPush() {

  // If mosaic not in zoom, and exit, go to the upper level (if exist)

  if (!IsInZoom()) {
    if (parent != nullptr) {
      parent->SetInZoom(false);
      parent->Invalidate();
    }
  } else {

    if(IsZoomOnSelected()) {
      selectedWidget->OnButtonBLongPush();

      if(IsMosaicActive()) ZoomOnSelected(false);

      Invalidate();

    } else {
      
      if (parent != nullptr) {
        SetMosaicActive(false);
        parent->SetMosaicActive(true);
        parent->InvalidateChildren();
      }

      SetInZoom(false);
      //Serial.println("No IsZoomOnSelected i No Zoom");
      Invalidate();

    }

  }
}


void WidgetMosaicComp::OnButtonCPressed() {

  if (!IsInZoom() && parent != nullptr) {

    // managed by the upper level

  } else {

    if(IsZoomOnSelected())

      return selectedWidget->OnButtonCPressed();

    else {

      children[indexSelected]->SetSelected(false);

      if(indexSelected < children.size()-1)
        indexSelected++;
      else 
          indexSelected = 0;

      children[indexSelected]->SetSelected(true);
      selectedWidget = children[indexSelected];     
    }
  }
}


Size WidgetMosaicComp::ComputeWidgetSize() {
  return ComputeWidgetSize(size,nbColumns, nbRows);
}

Size WidgetMosaicComp::ComputeWidgetSize(const Size& sizeParam, int32_t nbColumns, int32_t nbRows) {
  Size widgetSize;
  widgetSize.width = (sizeParam.width - ((2*border) + ((nbColumns-1)*border))) / nbColumns; // ERA 2 !!!
  widgetSize.height = (sizeParam.height - ((2*border) + ((nbRows-1)*border))) / nbRows;
  return widgetSize;
}

Point WidgetMosaicComp::ComputeWidgetPosition(const Size& widgetSize, const Point& pos, int32_t position) {
  Point widgetPosition;

  int32_t row = ((int32_t)position / (int32_t)nbColumns);
  int32_t column = position % nbColumns;
  widgetPosition.x = ((column)*border) + (column * widgetSize.width) + pos.x;
  widgetPosition.y = ((row)*border) + (row * widgetSize.height) + pos.y;

  return widgetPosition;
}

bool WidgetMosaicComp::IsZoomOnSelected() const {
  return (zoomOnSelected);
}

void WidgetMosaicComp::SetZoomOnSelected(bool zoom) {
  zoomOnSelected = zoom;
  selectedWidget->SetInZoom(zoom);
}


void WidgetMosaicComp::SetZoomOnSelectedCallback(std::function<void (Widget* widget, bool)>func) {
  zoomOnSelectedCallback = func;
}



