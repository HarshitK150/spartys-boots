/**
 * @file Badge.h
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef BADGE_H
#define BADGE_H

#include "../Item.h"

class Score;
/**
 * Class that implements a Badge
 */
class Badge : public Item
{
private:
  /// The underlying image that corresponds with the current badge achieved
  std::shared_ptr<wxImage> mCurrentBadgeImage = nullptr;

  /// The bitmap we can display for the current badge
  std::unique_ptr<wxBitmap> mCurrentBadgeBitmap;


  /// The type of badge the user has earned
  enum class Badges
  {
    LogicRookie,
    BooleanWarrior,
    SpartanGenius,
    NoneEarned
  };

  /// The badge the user has earned
  Badges mBadge = Badges::NoneEarned;

public:
  /// Default constructor (disabled)
  Badge() = delete;

  /// Copy constructor (disabled)
  Badge(const Badge &) = delete;

  /// Assignment operator
  void operator=(const Badge &) = delete;

  Badge(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override { visitor->VisitBadge(this); }

  // void XmlLoad(wxXmlNode *node) override

  /**
   * Draw the badge
   * @param gc The graphics context to draw on
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

 /**
   * Update the badge based on the score
   * @param score The score object
   */
  void UpdateBadge(Score *score);

  /**
   * Update the badge
   * @param elapsed The time since the last update
   */
  void Update(double elapsed) override;
};


#endif // BADGE_H
