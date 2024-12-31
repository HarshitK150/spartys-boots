/**
 * @file SensorGate.h
 * @author Nitish Maindoliya
 *
 */

#ifndef SENSORGATE_H
#define SENSORGATE_H

#include "../Gate.h"
#include "../Items/Product.h"
#include <memory>

/**
 * Class for the sensor gate
 */
class SensorGate : public Gate
{
public:
  /// Constructor (disabled)
  SensorGate() = delete;

  /// Copy constructor (disabled)
  SensorGate(const SensorGate &) = delete;

  /// Assignment operator (disabled)
  void operator=(const SensorGate &) = delete;

  SensorGate(Game *game, Product::Properties property);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override { visitor->VisitSensorGate(this); }

  /**
   * Draw the Sensor gate.
   * Override this method to draw the Sensor gate based on the output state.
   * @param gc Graphics context for drawing
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  int GetWidth() override;

  int GetHeight() override;

  void ComputeState() override;

  /**
   * Hit test for the Sensor gate.
   * @param x The x-coordinate of the mouse
   * @param y The y-coordinate of the mouse
   * @return false
   */
  bool HitTest(int x, int y) override { return false; }

  /**
   * Get the property associated with this gate.
   * @return The property of this gate.
   */
  Product::Properties GetProperty() const { return mProperty; }

private:
  /// The property associated with this gate (e.g., color, shape, or content)
  Product::Properties mProperty;
  /// The product image
  std::shared_ptr<wxImage> mSensorImage;
};

#endif // SENSORGATE_H
