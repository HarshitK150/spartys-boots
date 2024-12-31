/**
 * @file LevelScoreUpdateVisitor.h
 * @author Harshit Kandpal
 *
 *
 */
 
#ifndef LEVELSCOREUPDATEVISITOR_H
#define LEVELSCOREUPDATEVISITOR_H

#include "ItemVisitor.h"

/**
 * Class that represents a LevelScoreUpdateVisitor.
 */
class LevelScoreUpdateVisitor : public ItemVisitor {
private:
public:
    LevelScoreUpdateVisitor() {}

    void VisitScoreBoard(Scoreboard *scoreboard) override;
};



#endif //LEVELSCOREUPDATEVISITOR_H
