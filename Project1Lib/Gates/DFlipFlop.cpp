/**
 * @file DFlipFlop.cpp
 * @author Shashank Singh
 */

#include "../pch.h"
#include "DFlipFlop.h"

/// Size of the Flip Flop in pixels
/// @return Size of the gate
const wxSize DFlipFlopSize(50, 75);

/// Gap between the edge of the flip flop and the labels
const int DFlipFlopLabelMargin = 3;

/// How large the clock input triangle is in pixels width and height
const int DFlipFlopClockSize = 10;

/// Distance between pin circles and gate
const int DistanceCircleToGate = 20;


/**
 * Constructor
 * @param game Pointer to the game this gate is part of
 */
DFlipFlop::DFlipFlop(Game *game) :
  Gate(game)
{
  auto width = GetWidth();
  auto height = GetHeight();

  // Adding input pin for 'D' and clock
  AddInputPin(wxPoint(-width / 2 - DistanceCircleToGate, -(height / 4) + DFlipFlopLabelMargin),
              InputPinTypes::Data); // D input
  AddInputPin(wxPoint(-width / 2 - DistanceCircleToGate, height / 4 + DFlipFlopLabelMargin),
              InputPinTypes::Clock); // Clock input

  // Adding output pins for 'Q' and 'Q''
  AddOutputPin(wxPoint(width / 2 + DistanceCircleToGate, -(height / 4) + DFlipFlopLabelMargin)); // Q output
  AddOutputPin(wxPoint(width / 2 + DistanceCircleToGate, height / 4 + DFlipFlopLabelMargin), OutputPinTypes::Inverted); // Q' output

  SetState(States::Zero);
}


/**
 * Draw the D Flip Flop gate.
 * Override this method to draw the D Flip Flop gate based on the output state.
 * @param graphics Graphics context for drawing
 */
void DFlipFlop::Draw(const std::shared_ptr<wxGraphicsContext> &graphics)
{
  Gate::Draw(graphics);

  auto path = graphics->CreatePath();
  auto font = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);

  auto x = GetX();
  auto y = GetY();
  auto width = GetWidth();
  auto height = GetHeight();

  // Draw the rectangle body of the Flip Flop using DFlipFlopSize
  wxPoint2DDouble topLeft(x - width / 2, y - height / 2);
  wxPoint2DDouble bottomLeft(x - width / 2, y + height / 2);
  wxPoint2DDouble topRight(x + width / 2, y - height / 2);
  wxPoint2DDouble bottomRight(x + width / 2, y + height / 2);

  path.MoveToPoint(topLeft);
  path.AddLineToPoint(bottomLeft);
  path.AddLineToPoint(bottomRight);
  path.AddLineToPoint(topRight);
  path.AddLineToPoint(topLeft);
  path.CloseSubpath();

  // Draw the clock input triangle using DFlipFlopClockSize
  wxPoint2DDouble clockCenter(x - width / 4 - DFlipFlopLabelMargin, y + height / 4 + DFlipFlopLabelMargin);
  wxPoint2DDouble clockTop(clockCenter.m_x - DFlipFlopClockSize, clockCenter.m_y - DFlipFlopClockSize / 2);
  wxPoint2DDouble clockBottom(clockCenter.m_x - DFlipFlopClockSize, clockCenter.m_y + DFlipFlopClockSize / 2);

  path.MoveToPoint(clockCenter);
  path.AddLineToPoint(clockTop);
  path.MoveToPoint(clockCenter);
  path.AddLineToPoint(clockBottom);

  // Set pen and brush for the rectangle and the clock triangle
  graphics->SetPen(*wxBLACK_PEN);
  graphics->SetBrush(*wxWHITE_BRUSH);
  graphics->DrawPath(path);

  // Add labels for inputs and outputs inside the rectangle
  graphics->DrawText("D", x - width / 2 + DFlipFlopLabelMargin, y - height / 4 - DFlipFlopLabelMargin * 2);
  graphics->DrawText("Q", x + width / 4 - DFlipFlopLabelMargin, y - height / 4 - DFlipFlopLabelMargin * 2);
  graphics->DrawText("Q'", x + width / 4 - (DFlipFlopLabelMargin + 1), ///< The +1 accounts for the extra character
                     y + height / 4 - DFlipFlopLabelMargin * 2);
}

/**
 * Get the height of this AND gate
 * @return Height of this AND gate
 */
int DFlipFlop::GetHeight() { return DFlipFlopSize.GetHeight(); }

/**
 * Get the width of this AND gate
 * @return width of this AND gate
 */
int DFlipFlop::GetWidth() { return DFlipFlopSize.GetWidth(); }


/**
 * Compute the state of this DFlipFlop gate
 */
void DFlipFlop::ComputeState()
{
  std::shared_ptr<InputPin> clockPin;
  std::shared_ptr<InputPin> dPin;

  for (const auto &inputPin : GetInputPins())
  {
    if (inputPin->GetType() == InputPinTypes::Clock)
    {
      clockPin = inputPin;
    }
    else if (inputPin->GetType() == InputPinTypes::Data)
    {
      dPin = inputPin;
    }
  }

  if (clockPin->GetState() == States::One)
  {
    if (dPin->GetState() != States::Unknown)
    {
      SetState(dPin->GetState());
    }
  }

  Gate::ComputeState();
}
