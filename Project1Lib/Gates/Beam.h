/**
 * @file Beam.h
 * @author Nitish Maindoliya
 * @author Anas Shaaban
 */
#ifndef BEAM_H
#define BEAM_H

#include "../Gate.h"
#include "../Items/Product.h"

/**
 * Class for the beam
 */

/**
 * Class that implements an Beam
 */
class Beam : public Gate
{
private:
  /// Image for the beam sender and receiver when red
  std::shared_ptr<wxImage> mBeamRedImage;

  /// Image for the beam sender and receiver when green
  std::shared_ptr<wxImage> mBeamGreenImage;

  /// Image for the beam sender and receiver in its active state
  std::shared_ptr<wxImage> mActiveBeamImage;

  /// X offset for the beam pin in pixels
  int mSender;

  /// If True mirrors the item image
  bool mMirror = false;

  /// X offset for the beam pin in pixels
  const int mBeamPinOffset = 80;

  /// Bool that is true when a product is passing through the beam
  bool mBeamBroken = false;

public:
  /// Default constructor (disabled)
  Beam() = delete;

  /// Copy constructor (disabled)
  Beam(const Beam &) = delete;

  /// Assignment operator
  void operator=(const Beam &) = delete;

  Beam(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitBeam(this);
    visitor->VisitGates(this);
  }

  /**
   * Get sender value
   * @return sender value
   */
  int GetSender() const { return mSender; }

  void XmlLoad(wxXmlNode *node) override;

  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  /**
   * Set the beam broken state
   * @param broken True if beam is broken
   */
  void SetBeamBroken(bool broken);

  /**
   * Get the beam broken state
   * @return True if beam is broken
   */
  bool GetBeamBroken() { return mBeamBroken; }

  /**
   * Compute the state of the Beam gate
   */
  void ComputeState() override;

  /**
   * Get the sender for this gate
   * @return the sender offset
   */
  int GetSender() { return mSender; }
};

#endif // BEAM_H
