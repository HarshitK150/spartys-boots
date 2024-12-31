/**
 * @file NOTGate.cpp
 * @author Shashank Singh
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "NOTGate.h"

/// Set the size of the NOT gate in pixels
/// @return Size of the NOT gate
const wxSize NotGateSize(50, 50);

/// Radius of the circle in NOT gate
const double CircleRadius = 4.0;


/**
 * Constructor
 * @param game Pointer to the game this gate is part of
 */
NOTGate::NOTGate(Game *game) :
  Gate(game)
{
  auto width = GetWidth();

  AddInputPin(wxPoint(-width / 2 - DefaultLineLength, 0));
  AddOutputPin(wxPoint(width / 2 + DefaultLineLength, 0));
}

/**
 * Draws the NOT gate.
 * Override this method to draw the NOT gate based on the output state.
 * @param graphics Graphics context for drawing
 */
void NOTGate::Draw(const std::shared_ptr<wxGraphicsContext> &graphics)
{
  Gate::Draw(graphics);

  // Create a path to draw the NOT gate shape
  auto path = graphics->CreatePath();

  // The location and size of the NOT Gate
  auto x = GetX();
  auto y = GetY();
  auto w = GetWidth();
  auto h = GetHeight();

  // Define the points for the NOT gate shape
  wxPoint2DDouble p1(x - w / 2, y + h / 2); // Bottom left
  wxPoint2DDouble p2(x + w / 2, y); // Center right
  wxPoint2DDouble p3(x - w / 2, y - h / 2); // Top left

  // Create the path for the gate
  path.MoveToPoint(p1);
  path.AddLineToPoint(p2); // Draw line to center right
  path.AddLineToPoint(p3); // Draw line to top left
  path.CloseSubpath(); // Close the triangle shape

  // Draw the path
  graphics->SetPen(*wxBLACK_PEN);
  graphics->SetBrush(*wxWHITE_BRUSH);
  graphics->DrawPath(path);

  // Draw the circle for the NOT gate
  double circleX = x + w / 2 + CircleRadius / 2;
  double circleY = y;
  graphics->DrawEllipse(circleX - CircleRadius, circleY - CircleRadius, 2 * CircleRadius, 2 * CircleRadius);

}

/**
 * Get the width of this NOT gate
 * @return Width of this NOT gate
 */
int NOTGate::GetWidth()
{
  return NotGateSize.GetWidth();
}

/**
 * Get the height of this NOT gate
 * @return Height of this NOT gate
 */
int NOTGate::GetHeight()
{
  return NotGateSize.GetHeight();
}

/**
 * Compute the state of this NOT gate
 */
void NOTGate::ComputeState()
{
  auto input = GetInputPins()[0]->GetState();

  if (input == States::One)
  {
    SetState(States::Zero);
  }
  else if (input == States::Zero)
  {
    SetState(States::One);
  }
  else
  {
    SetState(States::Unknown);
  }

  Gate::ComputeState();
}
