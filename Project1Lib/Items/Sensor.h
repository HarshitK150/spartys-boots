/**
* @file Sensor.h
 * @author Nitish Maindoliya
 *
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "../Item.h"
#include "../Gates/SensorGate.h"
#include <vector>
#include <memory>
#include "../XmlLoader.h"

/**
 * Class for the sensor
 */
class Sensor : public Item
{
public:
  /// Default constructor (disabled)
  Sensor() = delete;

  /// Copy constructor (disabled)
  Sensor(const Sensor &) = delete;

  /// Assignment operator (disabled)
  void operator=(const Sensor &) = delete;

  /// Constructor for the Sensor class
  Sensor(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override { visitor->VisitSensor(this); }

  /**
   * Draw the sensor
   * @param gc The graphics context to draw on
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  /**
   * Load the attributes for a sensor from an XML node
   * @param node The XML node
   */
  void XmlLoad(wxXmlNode *node) override;

private:
  /// Image for the sensor camera
  std::shared_ptr<wxImage> mSensorCameraImage;
};

#endif // SENSOR_H
