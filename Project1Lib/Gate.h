/**
 * @file Gate.h
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 *
 */

#ifndef GATE_H
#define GATE_H


#include "Item.h"
#include <string>

#include "States.h"
#include "InputPin.h"
#include "OutputPin.h"

/**
 * Class for Gate
 */
class Gate : public Item
{
private:
  /// The state of the gate (Unknown, One, Zero)
  States mState = States::Unknown;

  /// The input pins of the gate
  std::vector<std::shared_ptr<InputPin>> mInputPins;

  /// The output pins of the gate
  std::vector<std::shared_ptr<OutputPin>> mOutputPins;

public:
  /// Default constructor (disabled)
  Gate() = delete;

  /// Copy constructor (disabled)
  Gate(const Gate &) = delete;

  /// Assignment operator
  void operator=(const Gate &) = delete;

  Gate(Game *game);

  /**
   * Draw the gate
   * @param gc The graphics context to draw on
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  bool HitTest(int x, int y) override;

  std::shared_ptr<IDraggable> HitDraggable(int x, int y) override;

  bool Catch(OutputPin *outputPin, wxPoint wireEnd) override;

  void SetControlPoints() override;

  void ResetControlPoints() override;

  /**
   * Move this gate to the front
   * of the list of items.
   */
  void MoveToFront() override {}

  /**
   * Release after moving
   */
  void Release() override {}

  /**
   * Add an input pin to the gate
   * @param location of the pin
   * @param type the type of pin
   */
  void AddInputPin(const wxPoint &location, InputPinTypes type = InputPinTypes::Regular)
  {
    mInputPins.push_back(std::make_shared<InputPin>(this, location, type));
  }

  /**
   * Add an output pin to the gate
   * @param location of the pin
   * @param type the type of pin
   */
  void AddOutputPin(const wxPoint &location, OutputPinTypes type = OutputPinTypes::Regular)
  {
    mOutputPins.push_back(std::make_shared<OutputPin>(this, location, type));
  }

  /**
   * Get the input pins of this gate
   * @return The input pins of this gate
   */
  std::vector<std::shared_ptr<InputPin>> GetInputPins() { return mInputPins; }

  /**
   * Get the output pins of this gate
   * @return The output pins of this gate
   */
  std::vector<std::shared_ptr<OutputPin>> GetOutputPins() { return mOutputPins; }

  /**
   * Compute the output state for a gate (virtual)
   */
  virtual void ComputeState();

  /**
   * Set state for a gate
   * @param state instance
   */
  void SetState(const States state) { mState = state; }

  /**
   * Get the state for a gate
   * @return the state of the gate
   */
  States GetState() const { return mState; }

  /**
   * Get the width of this gate
   * @return Width of this gate
   */
  virtual int GetWidth() { return 0; }

  /**
   * Get the height of this gate
   * @return Height of this gate
   */
  virtual int GetHeight() { return 0; }

  /**
   * Update the gate
   * @param elapsed The time since the last update
   */
  void Update(double elapsed) override;
};


#endif // GATE_H
