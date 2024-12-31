/**
 * @file SRFlipFlop.h
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef SRFLIPFLOP_H
#define SRFLIPFLOP_H

#include "../Gate.h"

/**
 * Class for SR Flip Flop
 */
class SRFlipFlop : public Gate
{
private:
public:
  // Default constructor (disabled)
  SRFlipFlop() = delete;

  // Copy constructor (disabled)
  SRFlipFlop(const SRFlipFlop &) = delete;

  // Assignment operator (disabled)
  void operator=(const SRFlipFlop &) = delete;

  SRFlipFlop(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitSRFlipFlop(this);
    visitor->VisitGates(this);
  }

  /**
   * Draw the gate
   * @param gc The graphics context we draw to
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  /**
   * Get the width of the gate
   * @return The width of the gate
   */
  int GetWidth() override;

  /**
   * Get the height of the gate
   * @return The height of the gate
   */
  int GetHeight() override;

  void ComputeState() override;
};


#endif // SRFLIPFLOP_H
