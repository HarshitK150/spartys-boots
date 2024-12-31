/**
 * @file BeamProductVisitor.cpp
 * @author Nitish Maindoliya
 */

#include "../pch.h"
#include "BeamProductVisitor.h"
#include <cmath>
#include "../Items/Product.h"
#include "../Gates/Beam.h"

/// Tolerance for beam intersection
static constexpr double BEAM_Y_TOLERANCE = 40.0;

/**
 * Constructor
 * @param beam The beam this visitor is associated with
 */
BeamProductVisitor::BeamProductVisitor(Beam *beam) :
  mBeam(beam)
{
}


/**
 * Visit a product to check for intersection with beam
 * @param product The product to check
 */
void BeamProductVisitor::VisitProduct(Product *product)
{
  if (!product->mIsCurrentlyDisplayed)
  {
    return;
  }

  // Get beam line coordinates
  double beamX = mBeam->GetX();
  double beamY = mBeam->GetY();
  double productX = product->GetX();
  double productY = product->GetY();

  // Get beam endpoints
  double senderX = beamX + mBeam->GetSender();
  double leftX = (beamX < senderX) ? beamX : senderX;
  double rightX = (beamX > senderX) ? beamX : senderX;

  // Check intersection
  if (productX >= leftX && productX <= rightX && std::abs(productY - beamY) < BEAM_Y_TOLERANCE)
  {
    mFoundIntersection = true;
    product->SetBeamHit(true);
  }
  else if (product->GetBeamHit())
  {
    product->SetBeamHit(false);
    product->HasLeftBeam();
  }
}

