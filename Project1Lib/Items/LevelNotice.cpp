/**
 * @file LevelNotice.cpp
 * @author Nitish Maindoliya
 */

#include "../pch.h"
#include "LevelNotice.h"
#include "../Game.h"

/// Images directory
const std::wstring DirectoryContainingImages = L"images/";

/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(24, 69, 59);

/// Color to draw a rectangle enclosing the level notice text
/// @return wxColour The color to draw the rectangle
wxColour LevelNoticeBackground(255, 255, 255, 200);

/// Padding to add to the left and right side of the level
/// notice background rectangle in virtual pixels
const double LevelNoticePadding = 20;


/**
 * Constructor
 * @param game The game this item is a member of
 * @param level The level to display
 * @param levelBegin True if the level begin notice, false if the level end notice
 */
LevelNotice::LevelNotice(Game *game, int level, bool levelBegin):
  Item(game)
{
  mLevel = level;
  mLevelBegin = levelBegin;
}

/**
 * Draw the Level Notice
 * @param gc The graphics context to draw on
 */
void LevelNotice::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  if (mIsDisplayed)
  {
    // Get the window or screen size
    int screenHeight = GetGame()->GetHeight();

    // Set the font
    auto font = gc->CreateFont(100, L"Arial", wxFONTFLAG_BOLD, LevelNoticeColor);
    gc->SetFont(font);

    if (mLevelBegin)
    {
      NoticeMessage = wxString::Format(L"Level %d Begin", mLevel);
    }
    int NoticeMessageWidth = (100 * NoticeMessage.length() / 2);

    // Calculate the centered position of the notice

    int xPos = NoticeMessageWidth / 3 - LevelNoticePadding;
    if (mLevelBegin)
    {
      xPos = NoticeMessageWidth / 2 - LevelNoticePadding;
    }

    int yPos = (screenHeight - NoticeSize) / 4;

    // Set a semi-transparent background brush
    wxBrush semiTransparentBrush(LevelNoticeBackground);
    gc->SetPen(*wxTRANSPARENT_PEN);
    gc->SetBrush(semiTransparentBrush);

    // Draw the background rectangle
    gc->DrawRectangle(xPos, yPos, NoticeMessageWidth + LevelNoticePadding * 2, NoticeSize + LevelNoticePadding);

    // Draw the "Level Complete" text
    gc->DrawText(NoticeMessage, xPos + LevelNoticePadding, yPos);
  }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void LevelNotice::Update(double elapsed)
{
  // Update mTimeElapsed is notice is displayed
  if (mIsDisplayed)
  {
    mTimeElapsed += elapsed;
  }

  // Remove notice from view if it has been displayed for LevelNoticeDuration
  if (mTimeElapsed >= LevelNoticeDuration)
  {
    mIsDisplayed = false;
    mTimeElapsed = 0;
  }
}
