/**
 * @file Sensor.cpp
 * @author Nitish Maindoliya
 */

#include "../pch.h"
#include "../Game.h"
#include "Sensor.h"
#include "../Gates/SensorGate.h"

#include <string>

/// The image file for the sensor cable
const std::wstring SensorCableImage = L"sensor-cable.png";

/// The image file for the sensor camera
const std::wstring SensorCameraImage = L"sensor-camera.png";

/// How far below Y location of the sensor system is the panel top?
const int PanelOffsetY = 87;

/// How much space for each property
/// @return wxSize The size of a property
const wxSize PropertySize(100, 40);

/// Size of a shape as a property in virtual pixels
const double PropertyShapeSize = 32;

/// Range where a product is viewed by the sensor relative
/// to the Y coordinate of the sensor.
const int SensorRange[] = {-40, 15};

/// The background color to draw the sensor panel
/// @return wxColour The color to use for the sensor panel background
const wxColour PanelBackgroundColor(128, 128, 128);

/**
 * Constructor
 * @param game Game this sensor is a member of
 */
Sensor::Sensor(Game *game) :
  Item(game)
{
}

/**
 * Draw the sensor
 * @param gc The graphics context to draw on
 */
void Sensor::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  // Draw the sensor camera
  auto sensorCameraImage = GetGame()->GetImage(SensorCameraImage);
  int sensorCameraCenterX = GetX();
  int sensorCameraCenterY = GetY();
  gc->DrawBitmap(*sensorCameraImage, sensorCameraCenterX - sensorCameraImage->GetWidth() / 2,
                 sensorCameraCenterY - sensorCameraImage->GetHeight() / 2,
                 sensorCameraImage->GetWidth(), sensorCameraImage->GetHeight());

  // Draw the sensor cable, starting directly beneath the camera
  auto sensorCableImage = GetGame()->GetImage(SensorCableImage);
  int cableStartX = sensorCameraCenterX - sensorCableImage->GetWidth() / 2;
  int cableStartY = sensorCameraCenterY - sensorCameraImage->GetHeight() / 2;
  gc->DrawBitmap(*sensorCableImage, cableStartX, cableStartY,
                 sensorCableImage->GetWidth(), sensorCableImage->GetHeight());
}

/**
 * Load the attributes for a sensor from an XML node
 * @param node The XML node
 */
void Sensor::XmlLoad(wxXmlNode *node)
{
  XmlLoader loader(GetGame());
  loader.LoadSensor(this, node);
}
