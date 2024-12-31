/**
 * @file Scoreboard.h
 * @author Harshit Kandpal
 *
 *
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Item.h"
#include "../Visitors/ItemVisitor.h"
#include "../Score.h"
#include "../XmlLoader.h"

/**
 * Class for the scoreboard
 */
class Scoreboard : public Item
{
private:
  /// The score object
  Score *mScore; // Reference to the score visitor object

  /// The text to display
  std::vector<std::string> mText; // Instructions to display

public:
  /// Default constructor (disabled)
  Scoreboard() = delete;

  /// Copy constructor (disabled)
  Scoreboard(const Scoreboard &) = delete;

  /// Assignment operator
  void operator=(const Scoreboard &) = delete;

  Scoreboard(Game *game, Score *score);

  /**
  * Accept a visitor
  * @param visitor The visitor we accept
  */
  void Accept(ItemVisitor *visitor) override { visitor->VisitScoreBoard(this); }

  void XmlLoad(wxXmlNode *node) override;

  /**
   * Draw the scoreboard
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  /**
   * Update the scoreboard
   * @param isCorrect True if the answer is correct, false otherwise
   */
  void UpdateScore(bool isCorrect);

  /**
   * Set the text to display
   * @param text The text to display
   */
  void SetText(const std::vector<std::string> &text) { mText = text; }

  /**
   * Get the text to display
   * @return The text to display
   */
  Score *GetScore() { return mScore; }

  /**
   * Reset the score
   */
  void ResetScore();

  void UpdateLevelChangeScore();
};


#endif // SCOREBOARD_H
