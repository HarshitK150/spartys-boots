/**
 * @file ORGate.cpp
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "ORGate.h"

/// Set the gate size
/// @return Size of the gate
const wxSize OrGateSize(75, 50);

/// Offset for the default length of line between pin and an OR gate
const int DefaultLineLengthOffset = 10;

/// Distance between the input pins
const int DistanceBetweenInputPins = 26;

/**
 * Constructor
 * @param game Pointer to the game this gate is part of
 */
ORGate::ORGate(Game *game) :
  Gate(game)
{
  auto width = GetWidth();
  auto height = GetHeight();

  AddInputPin(
    wxPoint(-width / 2 - DefaultLineLength + DefaultLineLengthOffset, -height / 2 + DistanceBetweenInputPins / 2));
  AddInputPin(
    wxPoint(-width / 2 - DefaultLineLength + DefaultLineLengthOffset, height / 2 - DistanceBetweenInputPins / 2));
  AddOutputPin(wxPoint(width / 2 + DefaultLineLength, 0));
}

/**
 * Draw the OR gate.
 * Override this method to draw the OR gate based on the output state.
 * @param graphics Graphics context for drawing
 */
void ORGate::Draw(const std::shared_ptr<wxGraphicsContext> &graphics)
{
  Gate::Draw(graphics);

  // Get the position and size
  auto x = GetX(); // Assume GetX() returns the X-coordinate of the gate
  auto y = GetY(); // Assume GetY() returns the Y-coordinate of the gate
  auto w = GetWidth();
  auto h = GetHeight();

  // Create a path to draw the OR gate shape
  auto path = graphics->CreatePath();

  // The three corner points of an OR gate
  wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
  wxPoint2DDouble p2(x + w / 2, y); // Center right
  wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

  // Control points used to create the Bezier curves
  auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
  auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
  auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

  // Create the path for the OR gate shape
  path.MoveToPoint(p1);
  path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
  path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
  path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
  path.CloseSubpath();

  // Set the pen and brush for the gate drawing
  graphics->SetPen(*wxBLACK_PEN);
  graphics->SetBrush(*wxWHITE_BRUSH);

  // Draw the OR gate shape
  graphics->DrawPath(path);
}

/**
 * Get the width of this OR gate
 * @return Width of this OR gate
 */
int ORGate::GetWidth() { return OrGateSize.GetWidth(); }

/**
 * Get the height of this OR gate
 * @return height of this OR gate
 */
int ORGate::GetHeight() { return OrGateSize.GetHeight(); }

/**
 * Compute the output state of the OR gate
 */
void ORGate::ComputeState()
{
  States state = States::Unknown;
  const std::vector<std::shared_ptr<InputPin>> inputPins = GetInputPins();

  const std::shared_ptr<InputPin> &inputPin1 = inputPins[0];
  const std::shared_ptr<InputPin> &inputPin2 = inputPins[1];

  if (inputPin1->GetState() == States::Unknown || inputPin2->GetState() == States::Unknown)
  {
    state = States::Unknown;
  }
  else if (inputPin1->GetState() == States::One || inputPin2->GetState() == States::One)
  {
    state = States::One;
  }
  else
  {
    state = States::Zero;
  }

  SetState(state);

  Gate::ComputeState();
}
