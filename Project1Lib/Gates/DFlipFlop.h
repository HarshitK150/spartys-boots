/**
 * @file DFlipFlop.h
 * @author Shashank Singh
 *
 *
 */

#ifndef DFLIPFLOP_H
#define DFLIPFLOP_H

#include "../Gate.h"

/**
 * Class that implements a Dflipflop Gate
 */
class DFlipFlop : public Gate
{
private:
public:
  /// Default constructor (disabled)
  DFlipFlop() = delete;

  /// Copy constructor (disabled)
  DFlipFlop(const DFlipFlop &) = delete;

  /// Assignment operator (disabled)
  void operator=(const DFlipFlop &) = delete;

  DFlipFlop(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitDFlipFlop(this);
    visitor->VisitGates(this);
  }

  void Draw(const std::shared_ptr<wxGraphicsContext> &graphics) override;

  int GetHeight() override;

  int GetWidth() override;

  void ComputeState() override;
};


#endif // DFLIPFLOP_H
