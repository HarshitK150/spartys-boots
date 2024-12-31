/**
 * @file ORGate.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ORGATE_H
#define PROJECT1_PROJECT1LIB_ORGATE_H

#include "../Gate.h"

/**
 * Class for OR Gate
 */
class ORGate : public Gate
{
public:
  /// Default constructor (disabled)
  ORGate() = delete;

  /// Copy constructor (disabled)
  ORGate(const ORGate &) = delete;

  /// Assignment operator (disabled)
  void operator=(const ORGate &) = delete;

  ORGate(Game *game);

  /**
  * Accept a visitor
  * @param visitor The visitor we accept
  */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitORGate(this);
    visitor->VisitGates(this);
  }

  void Draw(const std::shared_ptr<wxGraphicsContext> &graphics) override;

  int GetWidth() override;

  int GetHeight() override;

  void ComputeState() override;
};


#endif // PROJECT1_PROJECT1LIB_ORGATE_H
