/**
 * @file OutputPin.h
 * @author Harshit Kandpal
 * @author Nitish Maindoliya
 *
 */

#ifndef OUTPUTPIN_H
#define OUTPUTPIN_H

#include "States.h"
#include "Item.h"

class InputPin;
class Gate;

/// Maximum offset of Bezier control points relative to line ends
static constexpr double BezierMaxOffset = 200;

/// Line width for drawing lines between pins
static constexpr int LineWidth = 3;

/// Default length of line from the pin
static constexpr int DefaultLineLength = 20;

/**
 * Class for an output pin
 */
class OutputPin : public IDraggable
{
private:
  /// Gate that owns this output pin
  Gate *mGate = nullptr;

  /// Location of the output pin relative to the gate
  wxPoint mLocation;

  /// Current state of the pin
  States mState = States::Unknown;

  /// Type of the pin
  OutputPinTypes mType = OutputPinTypes::Regular;

  /// Location of the line end when dragging
  wxPoint mWireEnd;

  /// Are we dragging the line?
  bool mDragging = false;

  /// List of input pin caught
  std::vector<InputPin *> mCaught;

  /// Show control points for this output pin?
  bool mShowControlPoints = false;

public:
  /// Default constructor (disabled)
  OutputPin() = delete;

  /// Copy constructor (disabled)
  OutputPin(const OutputPin &) = delete;

  /// Assignment operator (disabled)
  void operator=(const OutputPin &) = delete;

  /// Constructor
  OutputPin(Gate *gate, wxPoint location, OutputPinTypes type = OutputPinTypes::Regular);

  void Draw(const std::shared_ptr<wxGraphicsContext> &gc);

  void SetLocation(double x, double y) override;

  void MoveToFront() override;

  void Release() override;

  bool HitTest(int x, int y);

  void SetCaught(InputPin *caught);

  void RemoveCaught(InputPin *caught);

  void SetControlPoints();

  void ResetControlPoints();

  /**
   * Get the state for a gate
   * @return the state of the gate
   */
  States GetState() const { return mState; }

  /**
   * Set state for a gate
   * @param state instance
   */
  void SetState(States state) { mState = state; }

  /**
   * Get the type for a gate
   * @return the type of the gate
   */
  OutputPinTypes GetType() const { return mType; }
};


#endif // OUTPUTPIN_H
