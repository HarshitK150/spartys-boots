/**
 * @file KickVisitor.h
 * @author Harshit Kandpal
 *
 *
 */

#ifndef KICKVISITOR_H
#define KICKVISITOR_H

#include "ItemVisitor.h"


/**
 * Visitor to perform the kick functionality
 */
class KickVisitor : public ItemVisitor
{
private:
  /// The beam object
  Beam *mBeam = nullptr;

  /// The sparty object
  Sparty *mSparty = nullptr;

public:
  /**
  * Constructor
  * @param sparty The sparty object
  */
  KickVisitor(Sparty *sparty);

  /**
  * Visit a product object
  * @param product The product we are visiting
  */
  void VisitProduct(Product *product) override;

  /**
  * Visit a beam object
  * @param beam The beam we are visiting
  */
  void VisitBeam(Beam *beam) override;
};


#endif //KICKVISITOR_H
