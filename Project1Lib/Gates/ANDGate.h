/**
 * @file ANDGate.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ANDGATE_H
#define PROJECT1_PROJECT1LIB_ANDGATE_H

#include "../Gate.h"

/**
 * Class that implements an AND gate
 */
class ANDGate : public Gate
{

private:
public:
  /// Default constructor (disabled)
  ANDGate() = delete;

  /// Copy constructor (disabled)
  ANDGate(const ANDGate &) = delete;

  /// Assignment operator (disabled)
  void operator=(const ANDGate &) = delete;

  ANDGate(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override
  {
    visitor->VisitANDGate(this);
  }

  void Draw(const std::shared_ptr<wxGraphicsContext> &graphics) override;

  /**
   * Get the width of the AND gate
   * @return The width of the AND gate
   */
  int GetWidth() override;

  /**
   * Get the height of the AND gate
   * @return The height of the AND gate
   */
  int GetHeight() override;

  /**
   * Compute the state of the AND gate
   */
  void ComputeState() override;
};

#endif // PROJECT1_PROJECT1LIB_ANDGATE_H
