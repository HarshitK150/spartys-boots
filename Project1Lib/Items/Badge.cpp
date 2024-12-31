/**
 * @file Badge.cpp
 * @author Nitish Maindoliya
 */

#include "../pch.h"
#include "Badge.h"

#include "../Game.h"
#include "../Score.h"

/// The location of the badge in virtual pixels.
/// @return wxPoint The location of the badge
const wxPoint Location(950, 150);

/// The value by which to image is to be scaled down
constexpr int Scale = 5;

/// Image for the badge when logic rookie is achieved
const std::wstring LogicRookieBadgeImage = L"logic-rookie-badge.png";

/// Image for the badge when boolean warrior is achieved
const std::wstring BooleanWarriorBadgeImage = L"boolean-warrior-badge.png";

/// Image for the badge when spartan genius is achieved
const std::wstring SpartanGeniusBadgeImage = L"spartan-genius-badge.png";

/// Score needed to earn badge Logic Rookie
static constexpr int LogicRookieScore = 30;

/// Score needed to earn badge Boolean Warrior
static constexpr int BooleanWarriorScore = 60;

/// Score needed to earn badge Spartan Genius
static constexpr int SpartanGeniusScore = 100;

/**
 * Constructor
 * @param game The game this Badge is a member of
 */
Badge::Badge(Game *game) :
  Item(game)
{
  // Set badge to Logic Rookie on initialization
  mBadge = Badges::LogicRookie;
  mCurrentBadgeImage = nullptr;

  SetX(Location.x);
  SetY(Location.y);
}

/**
 * Draw the badge
 * @param gc The graphics context to draw on
 */
void Badge::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  if (mCurrentBadgeImage != nullptr)
  {
    gc->DrawBitmap(*mCurrentBadgeImage, GetX(), GetY(), mCurrentBadgeImage->GetWidth() / Scale,
                   mCurrentBadgeImage->GetHeight() / Scale);
  }
}

/**
 * Update the badge
 * @param elapsed The time since the last update
 */
void Badge::Update(double elapsed)
{
  switch (mBadge)
  {
  case Badges::LogicRookie:
    mCurrentBadgeImage = GetGame()->GetImage(LogicRookieBadgeImage);
    break;
  case Badges::BooleanWarrior:
    mCurrentBadgeImage = GetGame()->GetImage(BooleanWarriorBadgeImage);
    break;
  case Badges::SpartanGenius:
    mCurrentBadgeImage = GetGame()->GetImage(SpartanGeniusBadgeImage);
    break;
  default:
    mCurrentBadgeImage = nullptr;
    break;
  }
}

/**
 * Update the badge based on the score
 * @param score The score object
 */
void Badge::UpdateBadge(Score *score)
{
  const double scoreValue = score->GetLevelScore() + score->GetGameScore();
  if (scoreValue >= SpartanGeniusScore)
  {
    mBadge = Badges::SpartanGenius;
  }
  else if (scoreValue >= BooleanWarriorScore)
  {
    mBadge = Badges::BooleanWarrior;
  }
  else if (scoreValue >= LogicRookieScore)
  {
    mBadge = Badges::LogicRookie;
  }
  else
  {
    mBadge = Badges::NoneEarned;
  }
}
