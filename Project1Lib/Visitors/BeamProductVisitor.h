/**
 * @file BeamProductVisitor.h
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef BEAMPRODUCTVISITOR_H
#define BEAMPRODUCTVISITOR_H
#include "ItemVisitor.h"

/**
 * Class that implements a Beam
 */
class BeamProductVisitor : public ItemVisitor
{
private:
  /// Pointer to the beam
  Beam *mBeam;

  /// Found intersection
  bool mFoundIntersection = false;

public:
  explicit BeamProductVisitor(Beam *beam);

  void VisitProduct(Product *product) override;

  /**
   * Visit a sensor to check for intersection with beam
   * @param beam
   */
  void VisitBeam(Beam *beam) override
  {
  }

  /**
   * Check if an intersection was found
   * @return True if an intersection was found
   */
  bool FoundIntersection() const { return mFoundIntersection; }
};


#endif //BEAMPRODUCTVISITOR_H
