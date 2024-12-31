/**
 * @file Scoreboard.cpp
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "Scoreboard.h"

#include "../Visitors/BadgeVisitor.h"
#include "../Game.h"

#include <regex>
#include <sstream>

/// Size of the scoreboard in virtual pixels
/// @return wxSize The size of the scoreboard
const wxSize ScoreboardSize(380, 100);

/// The spacing from the scores to the instructions presentation
/// in virtual pixels
const int SpacingScoresToInstructions = 40;

/// The spacing between the instruction lines in virtual pixels.
const int SpacingInstructionLines = 17;

/// Scoreboard padding
const int SpacingBoxToScores = 10;

/**
 * Constructor
 * @param game The game this scoreboard is a member of
 * @param score The score object
 */
Scoreboard::Scoreboard(Game *game, Score *score) :
  Item(game), mScore(score)
{
}

/**
 * Load the scoreboard from an XML node
 * @param node The XML node
 */
void Scoreboard::XmlLoad(wxXmlNode *node)
{
  XmlLoader loader(GetGame());
  loader.LoadScoreboard(this, node);
}

/**
 * Draw the scoreboard
 * @param gc The graphics context to draw on
 */
void Scoreboard::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  // Draw the background
  gc->SetPen(*wxBLACK);
  gc->SetBrush(*wxWHITE);
  gc->DrawRectangle(GetX(), GetY(), ScoreboardSize.GetWidth(), ScoreboardSize.GetHeight());

  // Score font
  auto font = gc->CreateFont(25, L"Arial", wxFONTFLAG_BOLD, wxColour(24, 69, 59));
  gc->SetFont(font);

  std::wostringstream level, game;
  level << L"Level: " << mScore->GetLevelScore(); // Fetch the level score from Score object
  game << L"Game: " << mScore->GetGameScore(); // Fetch the game score from Score object

  // Draw the scores
  gc->DrawText(level.str(), GetX() + SpacingBoxToScores, GetY() + SpacingBoxToScores);
  gc->DrawText(game.str(), GetX() + SpacingBoxToScores + ScoreboardSize.GetWidth() / 2.0, GetY() + SpacingBoxToScores);

  // Instructions font
  font = gc->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
  gc->SetFont(font);

  // Draw the instructions
  const double xLeft = GetX();
  double yTop = GetY() + SpacingScoresToInstructions + SpacingBoxToScores;
  for (const auto &line : mText)
  {
    gc->DrawText(line, xLeft + SpacingBoxToScores, yTop);
    yTop += SpacingInstructionLines;
  }
}

/**
 * Update the scoreboard
 * @param isCorrect True if the answer is correct, false otherwise
 */
void Scoreboard::UpdateScore(bool isCorrect)
{
  mScore->UpdateLevelScore(isCorrect);
  BadgeVisitor badgeVisitor(mScore);
  GetGame()->Accept(&badgeVisitor);
}

/**
 * Reset the Scoreboard's score to zero
 */
void Scoreboard::ResetScore()
{
  mScore->Reset();
}

/**
 * Update the scoreboard when levels change
 */
void Scoreboard::UpdateLevelChangeScore()
{
  mScore->EndLevel();
}
