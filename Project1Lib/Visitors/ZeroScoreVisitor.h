/**
 * @file ZeroScoreVisitor.h
 * @author Harshit Kandpal
 *
 *
 */

#ifndef ZEROSCOREVISITOR_H
#define ZEROSCOREVISITOR_H

#include "ItemVisitor.h"


class Product;

/**
 * Class that represents a ZeroScoreVisitor.
 */
class ZeroScoreVisitor : public ItemVisitor {
private:
public:
  void VisitScoreBoard(Scoreboard *scoreboard) override;
};



#endif //ZEROSCOREVISITOR_H
