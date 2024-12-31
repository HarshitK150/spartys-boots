/**
 * @file InputPin.h
 * @author Harshit Kandpal
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef INPUTPIN_H
#define INPUTPIN_H

#include "States.h"
#include "OutputPin.h"


class Gate;

/**
 * Class for InputPin
 */
class InputPin
{
private:
  /// What gate does this input pin belong to?
  Gate *mGate;

  /// The location of the input pin relative to the gate
  wxPoint mLocation;

  /// Current state of the pin
  States mState = States::Unknown;

  /// Type of the pin
  InputPinTypes mType;

  /// Output pin we are connected to
  OutputPin *mOutputPin = nullptr;

public:
  /// Default constructor (disabled)
  InputPin() = delete;

  /// Copy constructor (disabled)
  InputPin(const InputPin &) = delete;

  /// Assignment operator (disabled)
  void operator=(const InputPin &) = delete;

  /// Constructor
  InputPin(Gate *gate, wxPoint location, InputPinTypes type = InputPinTypes::Regular);

  //// Draw the input pin
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) const;

  /**
   * Update the state of the input pin
   */
  void Update()
  {
    if (mOutputPin)
    {
      mState = mOutputPin->GetState();
    }
  }

  bool Catch(OutputPin *outputPin, wxPoint wireEnd);

  /**
   * Get the absolute location of the input pin
   * @return The absolute location of the input pin
   */
  wxPoint GetAbsoluteLocation() const;

  /**
   * Set the input pin location in pixels relative to the gate
   * @param x X location
   * @param y Y location
   */
  void SetLocation(const int x, const int y) { mLocation = wxPoint(x, y); }

  /**
   * Set the input line that has caught this input pin
   * @param outputPin
   */
  void SetInputLine(OutputPin *outputPin);

  /**
   * Get the state of the input pin
   * @return The state of the input pin
   */
  States GetState() const { return mState; }

  /**
   * Get the type of the input pin
   * @return The type of the input pin
   */
  InputPinTypes GetType() const { return mType; }

  /**
   * Set state for a gate
   * @param state instance
   */
  // ONLY FOR TESTING
  void SetState(const States state) { mState = state; }
};


#endif // INPUTPIN_H
