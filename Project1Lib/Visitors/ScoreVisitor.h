/**
 * @file ScoreVisitor.h
 * @author Harshit Kandpal
 *
 *
 */
 
#ifndef SCOREVISITOR_H
#define SCOREVISITOR_H

#include "ItemVisitor.h"


class Product;

/**
 * Class for the score visitor
 */
class ScoreVisitor : public ItemVisitor {
private:

  /// The product we are visiting
  Product* mProduct = nullptr;

public:
  ScoreVisitor(Product *product);

  void VisitScoreBoard(Scoreboard *scoreboard) override;
};



#endif //SCOREVISITOR_H
