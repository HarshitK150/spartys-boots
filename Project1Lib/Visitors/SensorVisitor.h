/**
 * @file SensorVisitor.h
 * @author Bruno Budelmann 2024
 *
 *
 */

#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

#include "ItemVisitor.h"


/**
 * Visitor to set SensorGate state
 */
class SensorVisitor : public ItemVisitor
{
private:
  /// The beam we are visiting
  Beam *mBeam = nullptr;
  /// The sensor gate we are visiting
  SensorGate *mSensorGate = nullptr;
  /// The product we are visiting
  Product *mProduct = nullptr;

  /// Tolerance for the y coordinates of the beam and the product
  bool mFoundIntersection = false;

public:
  SensorVisitor(SensorGate *sensorGate);

  void VisitProduct(Product *product) override;

  void VisitBeam(Beam *beam) override;

  bool IsMatchingProduct() const;

  /**
   * Check if the product intersects the beam
   * @return True if an intersection is found
   */
  bool FoundIntersection() const { return mFoundIntersection; }
};


#endif //SENSORVISITOR_H
