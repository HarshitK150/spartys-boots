/**
 * @file KickVisitor.cpp
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "KickVisitor.h"

#include "../Gates/Sparty.h"
#include "../Gates/Beam.h"

/// Tolerance for beam intersection
static constexpr double BEAM_Y_TOLERANCE = 40.0;

/**
 * Constructor
 * @param sparty The sparty object
 */
KickVisitor::KickVisitor(Sparty *sparty) :
  mSparty(sparty)
{
}

/**
 * Visit a product object
 * @param product The product we are visiting
 */
void KickVisitor::VisitProduct(Product *product)
{
  if (!product->mIsCurrentlyDisplayed)
  {
    return;
  }

  // Get y coordinates for beam and the product coordinates
  double beamY = mBeam->GetY();
  double productY = product->GetY();

  // Check intersection
  if (std::abs(productY - beamY) < BEAM_Y_TOLERANCE)
  {
    product->SetMovingLeft();
  }
}

void KickVisitor::VisitBeam(Beam *beam)
{
  mBeam = beam;
}
