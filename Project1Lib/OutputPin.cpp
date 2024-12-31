/**
 * @file OutputPin.cpp
 * @author Harshit Kandpal
 * @author Nitish Maindoliya
 */

#include "pch.h"
#include "OutputPin.h"

#include "Game.h"
#include "Gate.h"

/// Diameter to draw the pin in pixels
static const int PinSize = 10;

/// Length of Plus lines
static const int PlusSize = 20;

/// Offset for Point labels
static const wxSize PointLabelOffset = wxSize(PlusSize / 4, PlusSize * -1.5);

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);

/**
 * Constructor
 * @param gate The gate this pin is a member of
 * @param location The location of the pin
 * @param type The type of the pin
 */
OutputPin::OutputPin(Gate *gate, const wxPoint location, OutputPinTypes type) :
    mGate(gate), mLocation(location), mType(type)
{
}

/**
 * Draw the output pin
 * @param gc The graphics context to draw on
 */
void OutputPin::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  int locationX = mGate->GetX() + mLocation.x;
  int locationY = mGate->GetY() + mLocation.y;

  wxColour color;
  switch (mState)
  {
  case States::Zero:
    color = ConnectionColorZero;
    break;
  case States::One:
    color = ConnectionColorOne;
    break;
  default:
    color = ConnectionColorUnknown;
    break;
  }

  // Set the pen for drawing
  gc->SetPen(wxPen(color, LineWidth));

  // Set the brush for drawing
  gc->SetBrush(wxBrush(color));

  // Draw the wire
  gc->StrokeLine(locationX, locationY, locationX - DefaultLineLength, locationY);

  // Set black pen for drawing the pin's circular borders
  gc->SetPen(*wxBLACK_PEN);

  // Draw the pin as a circle
  gc->DrawEllipse(locationX - PinSize / 2, locationY - PinSize / 2, PinSize, PinSize);

  // Reset the pen for drawing draggable wires
  gc->SetPen(wxPen(color, LineWidth));

  if(mDragging)
  {
    double distance = sqrt(pow((locationX - mWireEnd.x), 2) + pow((locationY - mWireEnd.y), 2));
    double offset = std::min(BezierMaxOffset, distance);

    wxPoint2DDouble p1(locationX, locationY); // p1
    wxPoint2DDouble p2(locationX + offset, locationY); // p2
    wxPoint2DDouble p3(mWireEnd.x - offset, mWireEnd.y); // p3

    wxGraphicsPath path = gc->CreatePath();

    path.MoveToPoint(p1);
    path.AddCurveToPoint(p2, p3, mWireEnd);

    gc->StrokePath(path);

    if (mShowControlPoints)
    {
      // Draw the red pluses
      gc->SetPen(*wxRED_PEN);

      gc->StrokeLine(p1.m_x - PlusSize/2, p1.m_y, p1.m_x + PlusSize/2, p2.m_y);
      gc->StrokeLine(p1.m_x, p1.m_y - PlusSize/2, p1.m_x, p2.m_y + PlusSize/2);

      gc->StrokeLine(p2.m_x - PlusSize/2, p2.m_y, p2.m_x + PlusSize/2, p2.m_y);
      gc->StrokeLine(p2.m_x, p2.m_y - PlusSize/2, p2.m_x, p2.m_y + PlusSize/2);

      gc->StrokeLine(p3.m_x - PlusSize/2, p3.m_y, p3.m_x + PlusSize/2, p3.m_y);
      gc->StrokeLine(p3.m_x, p3.m_y - PlusSize/2, p3.m_x, p3.m_y + PlusSize/2);

      gc->StrokeLine(mWireEnd.x - PlusSize/2, mWireEnd.y, mWireEnd.x + PlusSize/2, mWireEnd.y);
      gc->StrokeLine(mWireEnd.x, mWireEnd.y - PlusSize/2, mWireEnd.x, mWireEnd.y + PlusSize/2);

      // Draw the green parallelogram
      path = gc->CreatePath();
      gc->SetPen(*wxGREEN_PEN);

      path.MoveToPoint(p1.m_x, p1.m_y);
      path.AddLineToPoint(p2.m_x, p2.m_y);
      path.AddLineToPoint(mWireEnd.x, mWireEnd.y);
      path.AddLineToPoint(p3.m_x, p3.m_y);
      path.AddLineToPoint(p1.m_x, p1.m_y);
      gc->StrokePath(path);

      // Draw black labels for points p1, p2, p3, p3
      gc->SetPen(*wxBLACK_PEN);
      gc->DrawText(L"p1",p1.m_x + PointLabelOffset.x, p1.m_y + PointLabelOffset.y);
      gc->DrawText(L"p2",p2.m_x + PointLabelOffset.x, p2.m_y + PointLabelOffset.y);
      gc->DrawText(L"p3",p3.m_x + PointLabelOffset.x, p3.m_y + PointLabelOffset.y);
      gc->DrawText(L"p4",mWireEnd.x + PointLabelOffset.x, mWireEnd.y + PointLabelOffset.y);

    }
  }

  for (auto inputPin : mCaught)
  {
    // Reset the pen for drawing draggable wires
    gc->SetPen(wxPen(color, LineWidth));

    auto inputPinLocation = inputPin->GetAbsoluteLocation();

    double distance = sqrt(pow((locationX - inputPinLocation.x), 2) + pow((locationY - inputPinLocation.y), 2));
    double offset = std::min(BezierMaxOffset, distance);

    wxPoint2DDouble p1(locationX, locationY); // p1
    wxPoint2DDouble p2(locationX + offset, locationY); // p2
    wxPoint2DDouble p3(inputPinLocation.x - offset, inputPinLocation.y); // p3

    wxGraphicsPath path = gc->CreatePath();

    path.MoveToPoint(p1);
    path.AddCurveToPoint(p2, p3, inputPinLocation);

    gc->StrokePath(path);

    if (mShowControlPoints)
    {
      // Draw the red pluses
      gc->SetPen(*wxRED_PEN);

      gc->StrokeLine(p1.m_x - PlusSize/2, p1.m_y, p1.m_x + PlusSize/2, p2.m_y);
      gc->StrokeLine(p1.m_x, p1.m_y - PlusSize/2, p1.m_x, p2.m_y + PlusSize/2);

      gc->StrokeLine(p2.m_x - PlusSize/2, p2.m_y, p2.m_x + PlusSize/2, p2.m_y);
      gc->StrokeLine(p2.m_x, p2.m_y - PlusSize/2, p2.m_x, p2.m_y + PlusSize/2);

      gc->StrokeLine(p3.m_x - PlusSize/2, p3.m_y, p3.m_x + PlusSize/2, p3.m_y);
      gc->StrokeLine(p3.m_x, p3.m_y - PlusSize/2, p3.m_x, p3.m_y + PlusSize/2);

      gc->StrokeLine(inputPinLocation.x - PlusSize/2, inputPinLocation.y, inputPinLocation.x + PlusSize/2, inputPinLocation.y);
      gc->StrokeLine(inputPinLocation.x, inputPinLocation.y - PlusSize/2, inputPinLocation.x, inputPinLocation.y + PlusSize/2);

      // Draw the green parallelogram
      path = gc->CreatePath();
      gc->SetPen(*wxGREEN_PEN);

      path.MoveToPoint(p1.m_x, p1.m_y);
      path.AddLineToPoint(p2.m_x, p2.m_y);
      path.AddLineToPoint(inputPinLocation.x, inputPinLocation.y);
      path.AddLineToPoint(p3.m_x, p3.m_y);
      path.AddLineToPoint(p1.m_x, p1.m_y);
      gc->StrokePath(path);

      // Draw black labels for points p1, p2, p3, p3
      gc->SetPen(*wxBLACK_PEN);
      gc->DrawText(L"p1",p1.m_x + PointLabelOffset.x, p1.m_y + PointLabelOffset.y);
      gc->DrawText(L"p2",p2.m_x + PointLabelOffset.x, p2.m_y + PointLabelOffset.y);
      gc->DrawText(L"p3",p3.m_x + PointLabelOffset.x, p3.m_y + PointLabelOffset.y);
      gc->DrawText(L"p4",inputPinLocation.x + PointLabelOffset.x, inputPinLocation.y + PointLabelOffset.y);
    }
  }
}

/**
 * Set the location of the end of the wire as we drag it
 * @param x X location in pixels
 * @param y Y location in pixels
 */
void OutputPin::SetLocation(double x, double y)
{
  mDragging = true;
  mWireEnd = wxPoint(int(x), int(y));
}

/**
 * Did we click on the output pin?
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return Did we click on it?
 */
bool OutputPin::HitTest(int x, int y)
{
  double locationX = mGate->GetX() + mLocation.x;
  double locationY = mGate->GetY() + mLocation.y;

  return (locationX - x) * (locationX - x) + (locationY - y) * (locationY - y) < PinSize/2 * PinSize/2;
}

/**
 * Move the gate to the front
 */
void OutputPin::MoveToFront()
{
  mGate->GetGame()->MoveToFront(mGate);
}

/**
 * Release after moving
 */
void OutputPin::Release()
{
  if(mDragging)
  {
    // The mouse has been released. See if there
    // is an input pin we can catch?
    mGate->GetGame()->TryToCatch(this, mWireEnd);
  }

  mDragging = false;
}

/**
 * Set the caught input pin
 * @param caught Caught input pin
 */
void OutputPin::SetCaught(InputPin *caught)
{
  mCaught.push_back(caught);
  caught->SetInputLine(this);
}

/**
 * Remove the caught input pin
 * @param caught Caught input pin
 */
void OutputPin::RemoveCaught(InputPin *caught)
{
  mCaught.erase(std::remove(mCaught.begin(), mCaught.end(), caught), mCaught.end());
}


/**
 * Set the control points associated with this Output pin
 */
void OutputPin::SetControlPoints()
{
  mShowControlPoints = true;
}

/**
 * Reset the control points associated with this Output pin
 */
void OutputPin::ResetControlPoints()
{
  mShowControlPoints = false;
}