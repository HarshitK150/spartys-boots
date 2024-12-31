/**
 * @file ZeroScoreVisitor.cpp
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "ZeroScoreVisitor.h"

#include "../Items/Product.h"
#include "../Items/Scoreboard.h"

/**
 * Visit a Scoreboard object
 * @param scoreboard Scoreboard we are visiting
 */
void ZeroScoreVisitor::VisitScoreBoard(Scoreboard *scoreboard)
{
  scoreboard->ResetScore();
}
