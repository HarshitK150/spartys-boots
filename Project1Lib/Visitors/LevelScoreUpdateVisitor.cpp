/**
 * @file LevelScoreUpdateVisitor.cpp
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "LevelScoreUpdateVisitor.h"
#include "../Items/Scoreboard.h"

/**
 * Visit a ScoreBoard object
 * @param scoreboard ScoreBoard we are visiting
 */
void LevelScoreUpdateVisitor::VisitScoreBoard(Scoreboard *scoreboard)
{
    scoreboard->UpdateLevelChangeScore();
}
