/**
 * @file NOTGate.h
 * @author Shashank Singh
 *
 *
 */

#ifndef NOTGATE_H
#define NOTGATE_H

#include "../Gate.h"

/**
 * Class for NOT Gate
 */
class NOTGate : public Gate
{
private:
public:
  /// Default constructor (disabled)
  NOTGate() = delete;

  /// Copy constructor (disabled)
  NOTGate(const NOTGate &) = delete;

  /// Assignment operator (disabled)
  void operator=(const NOTGate &) = delete;

  NOTGate(Game *game);

  /**
  * Accept a visitor
  * @param visitor The visitor we accept
  */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitNOTGate(this);
    visitor->VisitGates(this);
  }

  void Draw(const std::shared_ptr<wxGraphicsContext> &graphics) override;

  int GetWidth() override;

  int GetHeight() override;

  void ComputeState() override;

  /// Radius of the circle in NOT gate
  const double CircleRadius = 4.0;
};


#endif // NOTGATE_H
