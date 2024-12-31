/**
 * @file ScoreVisitor.cpp
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "ScoreVisitor.h"

#include "../Items/Product.h"
#include "../Items/Scoreboard.h"

/**
 * Constructor
 * @param product The product this visitor is associated with
 */
ScoreVisitor::ScoreVisitor(Product *product) :
  mProduct(product)
{
}

/**
 * Visit a scoreboard to update the score
 * @param scoreboard The scoreboard to update
 */
void ScoreVisitor::VisitScoreBoard(Scoreboard *scoreboard)
{
  scoreboard->UpdateScore(!(mProduct->ShouldKick() ^ mProduct->IsMovingLeft()));
}
