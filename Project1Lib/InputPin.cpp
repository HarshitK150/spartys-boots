/**
 * @file InputPin.cpp
 * @author Harshit Kandpal
 * @author Nitish Maindoliya
 */

#include "pch.h"
#include "InputPin.h"

#include "Gate.h"

/// Diameter to draw the pin in pixels
const int PinSize = 10;

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
 * @param type The type of InputPin
 */
InputPin::InputPin(Gate *gate, const wxPoint location, InputPinTypes type) :
    mGate(gate), mLocation(location), mType(type)
{
}

/**
 * Draw the input pin
 * @param gc The graphics context to draw on
 */
void InputPin::Draw(const std::shared_ptr<wxGraphicsContext> &gc) const
{
  const double locationX = mGate->GetX() + mLocation.x;
  const double locationY = mGate->GetY() + mLocation.y;

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
  gc->StrokeLine(locationX, locationY, locationX + DefaultLineLength, locationY);


  // Set black pen for drawing the pin's circular borders
  gc->SetPen(*wxBLACK_PEN);

  // Draw the pin as a circle
  gc->DrawEllipse(locationX - PinSize / 2.0, locationY - PinSize / 2.0, PinSize, PinSize);
}

/**
 * Try to catch an input pin at the new x,y location of the rod end
 * @param outputPin Output pin we are trying to catch from
 * @param wireEnd The wire end point
 * @return true if caught
 */
bool InputPin::Catch(OutputPin *outputPin, wxPoint wireEnd)
{
  auto loc = GetAbsoluteLocation();
  auto relative = wireEnd - loc;

  if ((relative.x * relative.x + relative.y * relative.y) < PinSize / 2 * PinSize / 2)
  {
    if (mOutputPin != nullptr)
    {
      mOutputPin->RemoveCaught(this);
    }

    outputPin->SetCaught(this);
    mOutputPin = outputPin;
  }

  return false;
}

/**
 * Get the location of the InputPin in pixels, not relative to the gate
 * @return Location in pixels
 */
wxPoint InputPin::GetAbsoluteLocation() const
{
  const double InputPinX = mGate->GetX() + mLocation.x;
  const double InputPinY = mGate->GetY() + mLocation.y;

  return wxPoint(InputPinX, InputPinY);
}

/**
 * Set the input line that has caught this input pin
 * @param outputPin
 */
void InputPin::SetInputLine(OutputPin *outputPin)
{
  mOutputPin = outputPin;

  mState = outputPin->GetState();
}
