/**
 * @file SensorVisitor.cpp
 * @author Bruno Budelmann 2024
 */

#include "../pch.h"
#include "SensorVisitor.h"
#include "../Gates/SensorGate.h"
#include "../Gates/Beam.h"

/// Tolerance for sensor detection below the beam
static constexpr double BEAM_BOTTOM_Y_TOLERANCE = 40.0;
/// Tolerance for sensor detection above the beam
static constexpr double BEAM_TOP_Y_TOLERANCE = 100.0;

/**
 * Constructor
 * @param sensorGate The sensor gate we are visiting
 */
SensorVisitor::SensorVisitor(SensorGate *sensorGate) :
  mSensorGate(sensorGate)
{
}

/**
 * Visit a Product object
 * @param product Product object we are visiting
 */
void SensorVisitor::VisitProduct(Product *product)
{
  if (!product->mIsCurrentlyDisplayed)
  {
    return;
  }

  // Get y coordinates for beam and the product coordinates
  double beamY = mBeam->GetY();
  double productY = product->GetY();

  // Check intersection
  if (productY >= beamY)
  {
    if (std::abs(beamY - productY) < BEAM_BOTTOM_Y_TOLERANCE)
    {
      mFoundIntersection = true;
      mProduct = product;
    }
  }
  else
  {
    if (std::abs(beamY - productY) < BEAM_TOP_Y_TOLERANCE)
    {
      mFoundIntersection = true;
      mProduct = product;
    }
  }
}

/**
 * Visit a Beam object
 * @param beam Beam object we are visiting
 */
void SensorVisitor::VisitBeam(Beam *beam)
{
  mBeam = beam;
}

/**
 * Check if the product matches the sensor gate
 * @return True if the product matches the sensor gate
 */
bool SensorVisitor::IsMatchingProduct() const
{
  if (!mFoundIntersection || !mProduct)
    return false;

  auto propertyType = Product::PropertiesToTypes.find(mSensorGate->GetProperty());
  if (propertyType == Product::PropertiesToTypes.end())
    return false;

  switch (propertyType->second)
  {
  case Product::Types::Color:
    return mProduct->GetColor() == mSensorGate->GetProperty();
  case Product::Types::Shape:
    return mProduct->GetShape() == mSensorGate->GetProperty();
  case Product::Types::Content:
    return mProduct->GetContent() == mSensorGate->GetProperty();
  default:
    return false;
  }
}
