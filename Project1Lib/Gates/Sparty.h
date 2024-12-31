/**
 * @file Sparty.h
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef SPARTY_H
#define SPARTY_H

#include "../Gate.h"

/**
 * Class for Sparty
 */
class Sparty : public Gate
{
private:
  /// The height of the sparty in virtual pixels
  int mHeight{};
  /// Speed of product moving off the belt
  double mKickSpeed{};
  /// Length of kick animation in seconds
  double mKickDuration{};
  /// The X location of the input pin
  double mPinX{};
  /// The Y location of the input pin
  double mPinY{};

  /// Animation state
  bool mKicking = false;
  /// Time duration of the kick
  double mKickTime = 0;
  /// Animation completion
  bool mProductKicked = false;

public:
  /// Default constructor (disabled)
  Sparty() = delete;

  /// Copy constructor (disabled)
  Sparty(const Sparty &) = delete;

  /// Assignment operator
  void operator=(const Sparty &) = delete;

  Sparty(Game *game);

  /**
  * Accept a visitor
  * @param visitor The visitor we accept
  */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitSparty(this);
    visitor->VisitGates(this);
  }

  void XmlLoad(wxXmlNode *node) override;

  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  void Update(double elapsed) override;

  void Kick();

  void KickProduct(std::shared_ptr<Product> product);

  void DrawBoot(const std::shared_ptr<wxGraphicsContext> &gc, int width, int height);

  double GetBootRotation();

  /**
  * Set the height for sparty
  * @param height value for height
  */
  void SetHeight(int height) { mHeight = height; }

  /**
  * Set the kick speed for sparty
  * @param speed value for speed
  */
  void SetKickSpeed(double speed) { mKickSpeed = speed; }

  /**
  * Set the kick duration for sparty
  * @param duration value for duration
  */
  void SetKickDuration(double duration) { mKickDuration = duration; }

  /**
  * Set the pin for sparty
  * @param x value for x location
  * @param y value for y location
  */
  void SetPin(double x, double y)
  {
    mPinX = x;
    mPinY = y;
  }

  void ComputeState() override;

};


#endif // SPARTY_H
