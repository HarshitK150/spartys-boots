/**
 * @file LevelNotice.h
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 *
 */

#ifndef LEVELNOTICE_H
#define LEVELNOTICE_H

#include "../Item.h"

/**
 * Class for Level Notice
 */
class LevelNotice : public Item
{
private:
  /// Time Elapsed since the notice is displayed
  double mTimeElapsed = 0;

  /// True if the notice is displayed, false otherwise
  bool mIsDisplayed = true;

  /// The level which the beginning notice is being displayed for
  int mLevel = 0;

  /// True if the is beginning message is to be displayed, false if the ending message
  bool mLevelBegin = true;

  /// Notice Message to be Displayed, defaults to "Level Complete"
  wxString NoticeMessage = wxString::Format(L"Level Complete!");

public:
  /// Default constructor (disabled)
  LevelNotice() = delete;

  /// Copy constructor (disabled)
  LevelNotice(const LevelNotice &) = delete;

  /// Assignment operator
  void operator=(const LevelNotice &) = delete;

  LevelNotice(Game *game, int level, bool levelBegin);

  /**
  * Accept a visitor
  * @param visitor The visitor we accept
  */
  void Accept(ItemVisitor *visitor) override { visitor->VisitLevelNotice(this); }

  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  /**
   * Handle updates for animation
   * @param elapsed The time since the last update
   */
  void Update(double elapsed) override;
};


#endif // LEVELNOTICE_H
