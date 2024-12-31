/**
 * @file Score.h
 * @author Bruno Budelmann 2024
 *
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include "Visitors/ItemVisitor.h"

/**
 *
 * Class for Score
 *
 */
class Score : public ItemVisitor
{
private:
  /// Current level score
  int mLevelScore = 0;
  /// Total game score
  int mGameScore = 0;
  /// Points for a correct kick
  int mGood = 10;
  /// Points for an incorrect kick
  int mBad = -5;

public:
  /// Default constructor
  Score();

  /**
   * Sets the points for a correct kick/not kick
   * @param good the points for a correct kick/not kick
   */
  void SetGoodScore(int good) { mGood = good; }

  /**
   * Sets the points for an incorrect kick/not kick
   * @param bad the points for an incorrect kick/not kick
   */
  void SetBadScore(int bad) { mBad = bad; }

  void UpdateLevelScore(bool isCorrect);

  void EndLevel();

  /**
   * Gets the points for the level score
   * @return mLevelScore the points for the level score
   */
  int GetLevelScore() const { return mLevelScore; }

  /**
   * Gets the points for the game score
   * @return mGameScore the points for the game score
   */
  int GetGameScore() const { return mGameScore; }


  void Reset();

  /**
   * Resets the level and game score
   */
  void HardReset()
  {
    mLevelScore = 0;
    mGameScore = 0;
  }
};

#endif // SCORE_H
