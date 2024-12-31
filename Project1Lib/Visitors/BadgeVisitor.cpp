/**
 * @file BadgeVisitor.cpp
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "BadgeVisitor.h"

#include "../Items/Badge.h"

/**
 * Constructor
 * @param score The score object
 */
BadgeVisitor::BadgeVisitor(Score *score) :
  mScore(score)
{
}

/**
 * Visit a badge object
 * @param badge The badge we are visiting
 */
void BadgeVisitor::VisitBadge(Badge *badge)
{
  badge->UpdateBadge(mScore);
}
