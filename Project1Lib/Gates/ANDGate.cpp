/**
 * @file ANDGate.cpp
 * @authors Nitish Maindoliya, Harshit Kandpal, Shashank Singh, Anas Shabaan, Bruno Budelman
 */

#include "../pch.h"
#include "ANDGate.h"
#include <cmath>

/// Size of the AND gate in pixels
/// @return Size of the AND gate
const wxSize AndGateSize(75, 50);

/// How far the Bezier control points are for the AND
/// gate to the right of ends of the curve as a percentage
/// of the gate height.
const double AndGateControlPointOffset = 0.75;

/// Distance between the input pins
const int DistanceBetweenInputPins = 26;

/**
 * Constructor
 * @param game Pointer to the game this gate is part of
 */
ANDGate::ANDGate(Game *game) :
  Gate(game)
{
  auto width = GetWidth();
  auto height = GetHeight();

  AddInputPin(wxPoint(-width / 2 - DefaultLineLength, -height / 2 + DistanceBetweenInputPins / 2));
  AddInputPin(wxPoint(-width / 2 - DefaultLineLength, height / 2 - DistanceBetweenInputPins / 2));
  AddOutputPin(wxPoint(width / 2 + DefaultLineLength, 0));
}

/**
 * Draw the AND gate.
 * Override this method to draw the AND gate based on the output state.
 * @param gc gc context for drawing
 */
void ANDGate::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  Gate::Draw(gc);

  auto path = gc->CreatePath();

  auto x = GetX();
  auto y = GetY();
  auto width = GetWidth();
  auto height = GetHeight();

  wxPoint2DDouble topLeft(x - width / 2, y - height / 2);
  wxPoint2DDouble bottomLeft(x - width / 2, y + height / 2);
  wxPoint2DDouble topRight(x + width / 8, y - height / 2);
  wxPoint2DDouble bottomRight(x + width / 8, y + height / 2);

  auto controlPointOffset = wxPoint2DDouble(height * AndGateControlPointOffset, 0);

  path.MoveToPoint(topLeft);
  path.AddLineToPoint(bottomLeft);
  path.AddLineToPoint(bottomRight);
  path.AddCurveToPoint(bottomRight + controlPointOffset, topRight + controlPointOffset, topRight);
  path.AddLineToPoint(topLeft);
  path.CloseSubpath();

  gc->SetPen(*wxBLACK_PEN);
  gc->SetBrush(*wxWHITE_BRUSH);

  gc->DrawPath(path);
}

/**
 * Get the width of this AND gate
 * @return Width of this AND gate
 */
int ANDGate::GetWidth() { return AndGateSize.GetWidth(); }

/**
 * Get the height of this AND gate
 * @return Height of this AND gate
 */
int ANDGate::GetHeight() { return AndGateSize.GetHeight(); }

/**
 * Compute the output state of the AND gate
 */
void ANDGate::ComputeState()
{
  States state = States::Unknown;
  const std::vector<std::shared_ptr<InputPin>> inputPins = GetInputPins();

  const std::shared_ptr<InputPin> &inputPin1 = inputPins[0];
  const std::shared_ptr<InputPin> &inputPin2 = inputPins[1];

  if (inputPin1->GetState() == States::Unknown || inputPin2->GetState() == States::Unknown)
  {
    state = States::Unknown;
  }
  else if (inputPin1->GetState() == States::One && inputPin2->GetState() == States::One)
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
