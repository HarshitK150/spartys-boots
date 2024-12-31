/**
 * @file SRFlipFlop.cpp
 * @author Nitish Maindoliya
 */

#include "../pch.h"
#include "SRFlipFlop.h"

/// Size of the Flip Flop in pixels
/// @return The size of the Flip Flop
const wxSize SRFlipFlopSize(50, 75);

/// Gap between the edge of the flip flop and the labels
const int SRFlipFlopLabelMargin = 3;

/// Distance between pin circles and gate
const int DistanceCircleToGate = 20;

/**
 * Constructor
 * @param game Pointer to the game this gate is part of
 */
SRFlipFlop::SRFlipFlop(Game *game) :
  Gate(game)
{
  auto width = GetWidth();
  auto height = GetHeight();

  // Adding input pin for 'S' and 'R'
  AddInputPin(wxPoint(-width / 2 - DistanceCircleToGate, -(height / 4) + SRFlipFlopLabelMargin),
              InputPinTypes::Set); // Set input
  AddInputPin(wxPoint(-width / 2 - DistanceCircleToGate, height / 4 + SRFlipFlopLabelMargin),
              InputPinTypes::Reset); // Reset input

  // Adding output pins for 'Q' and 'Q'
  AddOutputPin(wxPoint(width / 2 + DistanceCircleToGate, -(height / 4) + SRFlipFlopLabelMargin)); // Q output
  AddOutputPin(wxPoint(width / 2 + DistanceCircleToGate, height / 4 + SRFlipFlopLabelMargin), OutputPinTypes::Inverted); // Q' output

  SetState(States::Zero);
}

void SRFlipFlop::Draw(const std::shared_ptr<wxGraphicsContext> &graphics)
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

  // Set pen and brush for the rectangle and the clock triangle
  graphics->SetPen(*wxBLACK_PEN);
  graphics->SetBrush(*wxWHITE_BRUSH);
  graphics->DrawPath(path);

  // Add labels for inputs and outputs inside the rectangle
  graphics->DrawText("S", x - width / 2 + SRFlipFlopLabelMargin, y - height / 4 - SRFlipFlopLabelMargin * 2);
  graphics->DrawText("R", x - width / 2 + SRFlipFlopLabelMargin, y + height / 4 - SRFlipFlopLabelMargin * 2);


  graphics->DrawText("Q", x + width / 4 - SRFlipFlopLabelMargin, y - height / 4 - SRFlipFlopLabelMargin * 2);
  graphics->DrawText("Q'", x + width / 4 - (SRFlipFlopLabelMargin + 1), ///< The +1 accounts for the extra character
                     y + height / 4 - SRFlipFlopLabelMargin * 2);
}

int SRFlipFlop::GetHeight() { return SRFlipFlopSize.GetHeight(); }

int SRFlipFlop::GetWidth() { return SRFlipFlopSize.GetWidth(); }

/**
 * Compute the output state of the SRFlipFLop gate
 */
void SRFlipFlop::ComputeState()
{
  std::shared_ptr<InputPin> setPin;
  std::shared_ptr<InputPin> resetPin;

  for (auto pin : GetInputPins())
  {
    if (pin->GetType() == InputPinTypes::Set)
    {
      setPin = pin;
    }
    else if (pin->GetType() == InputPinTypes::Reset)
    {
      resetPin = pin;
    }
  }

  if (setPin->GetState() == States::One && resetPin->GetState() == States::One)
  {
    SetState(States::Unknown);
  }
  else if (setPin->GetState() == States::One)
  {
    SetState(States::One);
  }
  else if (resetPin->GetState() == States::One)
  {
    SetState(States::Zero);
  }

  Gate::ComputeState();
}
