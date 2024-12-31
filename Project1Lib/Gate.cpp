/**
 * @file Gate.cpp
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 */

#include "pch.h"
#include "Gate.h"

/**
 * Constructor
 * @param game Game this gate is a member of
 */
Gate::Gate(Game *game) :
  Item(game)
{
}

/**
 * Draw the gate
 * @param gc The graphics context to draw on
 */
void Gate::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  for (const auto &inputPin : mInputPins)
  {
    inputPin->Draw(gc);
  }

  for (const auto &outputPin : mOutputPins)
  {
    outputPin->Draw(gc);
  }
}

/**
 * Test to see if we hit this gate with mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Gate::HitTest(int x, int y)
{
  double wid = GetWidth();
  double hit = GetHeight();

  // Make x and y relative to the top-left corner of the gate
  // Subtracting the center makes x, y relative to the gate center
  // Adding half the size makes x, y relative to the gate top corner
  double testX = x - GetX() + wid / 2;
  double testY = y - GetY() + hit / 2;

  // Test to see if x, y are in the gate
  if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
  {
    // We are outside the gate
    return false;
  }

  return true;
}

/**
 * Test to see if we clicked on some draggable inside the gate.
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return Whatever we clicked on or NULL if none
 */
std::shared_ptr<IDraggable> Gate::HitDraggable(int x, int y)
{
  for (auto outputPin : mOutputPins)
  {
    if (outputPin->HitTest(x, y))
    {
      return outputPin;
    }
  }

  return nullptr;
}

/**
 * Try to catch an input pin at the new x,y location of the wire end
 * @param outputPin Output pin we are trying to catch from
 * @param wireEnd The wire end point
 * @return true if caught
 */
bool Gate::Catch(OutputPin *outputPin, wxPoint wireEnd)
{
  bool output = false;
  for (const auto& inputPin : mInputPins)
  {
    output = inputPin->Catch(outputPin, wireEnd);

    if (output)
    {
      return output;
    }
  }
  return output;
}

/**
 * Set the control points associated with this gate
 */
void Gate::SetControlPoints()
{
  for (const auto& outputPin : mOutputPins)
  {
    outputPin->SetControlPoints();
  }
}

/**
 * Reset the control points associated with this gate
 */
void Gate::ResetControlPoints()
{
  for (const auto& outputPin : mOutputPins)
  {
    outputPin->ResetControlPoints();
  }
}

void Gate::Update(double elapsed)
{
  for (const auto& inputPin : mInputPins)
  {
    inputPin->Update();
  }

  ComputeState();
}

void Gate::ComputeState()
{
  // Default implementation forwards the state of the gate to the output pins

  for (const auto& outputPin : mOutputPins)
  {
    if (outputPin->GetType() == OutputPinTypes::Regular)
    {
      outputPin->SetState(GetState());
    }
    else
    {
      if (GetState() == States::One)
      {
        outputPin->SetState(States::Zero);
      }
      else if (GetState() == States::Zero)
      {
        outputPin->SetState(States::One);
      }
      else
      {
        outputPin->SetState(States::Unknown);
      }
    }
  }
}
