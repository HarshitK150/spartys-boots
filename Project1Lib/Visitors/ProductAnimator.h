/**
 * @file ProductAnimator.h
 * @author Your Name
 */
#ifndef PRODUCTANIMATOR_H
#define PRODUCTANIMATOR_H

#include "ItemVisitor.h"
#include "../Items/Product.h"

/// Speed with which product moves off conveyor once kicked
static constexpr int MovingLeftSpeed = 75;

/**
 * Visitor to handle product animation and reset
 */
class ProductAnimator : public ItemVisitor
{
private:
  double mElapsed; ///< Time elapsed since last update
  double mSpeed; ///< Conveyor speed
  bool mIsRunning; ///< Is conveyor running?
  double mGameHeight; ///< Game window height
  double mX; ///< Conveyor X position
  double mY; ///< Conveyor Y position
  bool mIsReset; ///< Is this a reset operation?
  Conveyor *mConveyor; ///< Conveyor

public:
  /**
   * Constructor
   * @param conveyor Conveyor instance
   * @param elapsed Time elapsed since last update
   * @param gameHeight Height of game window
   * @param isReset Whether this is a reset operation
   */
  ProductAnimator(Conveyor *conveyor, const double elapsed, const double gameHeight, const bool isReset = false):
      mElapsed(elapsed), mGameHeight(gameHeight), mIsReset(isReset), mConveyor(conveyor)
  {
    mSpeed = conveyor->GetSpeed();
    mIsRunning = conveyor->IsRunning();
    mX = conveyor->GetX();
    mY = conveyor->GetY();
  }

  /**
   * Visit a product
   * @param product Product to visit
   */
  void VisitProduct(Product *product) override
  {
    if (mIsReset)
    {
      // Reset the product position
      product->SetX(mX);
      product->SetY(mY - product->GetPlacement());
      product->mIsCurrentlyDisplayed = true;
      return;
    }

    if (!product->mIsCurrentlyDisplayed)
    {
      return;
    }

    if (mIsRunning && !product->IsMovingLeft())
    {
      // Move product with conveyor at scaled speed
      const double newY = product->GetY() + (mElapsed * mSpeed);
      product->SetY(newY);

      if (product->GetY() > mGameHeight)
      {
        product->mIsCurrentlyDisplayed = false;
      }
    }
    else if (product->IsMovingLeft())
    {
      const double x = product->GetX();
      product->SetX(x - MovingLeftSpeed);

      if (x < -mConveyor->GetX())
      {

        product->mIsCurrentlyDisplayed = false;

        product->SetMovingLeft(false);
      }
    }
  }
};

#endif // PRODUCTANIMATOR_H
