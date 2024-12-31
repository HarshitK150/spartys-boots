/**
 * @file Score.cpp
 * @author Bruno Budelmann 2024
 */

#include "pch.h"
#include "Score.h"

/**
 * Constructor
 */
Score::Score() {}


/**
 * Update the score
 * @param isCorrect bool based on product kicking
 */
void Score::UpdateLevelScore(bool isCorrect)
{
  if (isCorrect) {
    mLevelScore += mGood;  // Correct kick
  } else {
    mLevelScore += mBad;   // Incorrect kick
  }
}

/**
 * End the Level
 * Add the Score
 */
void Score::EndLevel()
{
  mGameScore += mLevelScore;  // Add the level score to the total game score
  mLevelScore = 0;            // Reset the level score
}

/**
 * Reset the level score
 */
void Score::Reset()
{
  mLevelScore = 0;
}
