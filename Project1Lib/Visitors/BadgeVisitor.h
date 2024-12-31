/**
 * @file BadgeVisitor.h
 * @author Harshit Kandpal
 *
 *
 */

#ifndef BADGEVISITOR_H
#define BADGEVISITOR_H

#include "ItemVisitor.h"

class Score;
/**
 * Class that implements a Badge Visitor
 */
class BadgeVisitor : public ItemVisitor
{
private:
  /// The score object
  Score *mScore;

public:
  /**
  * Constructor
  * @param score The score object
  */
  BadgeVisitor(Score *score);

  void VisitBadge(Badge *badge) override;

};


#endif //BADGEVISITOR_H
