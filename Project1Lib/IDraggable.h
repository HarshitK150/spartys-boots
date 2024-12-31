/**
 * @file IDraggable.h
 * @authors Nitish Maindoliya
 *
 */

#ifndef IDRAGGABLE_H
#define IDRAGGABLE_H

/**
 * Interface for draggable things
 */
class IDraggable
{
public:
  /**
   * Set the location of the draggable thing
   * @param x X location in pixels
   * @param y Y location in pixels
   */
  virtual void SetLocation(double x, double y) = 0;

  /**
   * This draggable thing should be moved to the front
   * of the list of items.
   */
  virtual void MoveToFront() = 0;

  /**
   * Release after moving
   */
  virtual void Release() = 0;

  /**
   * Destructor
   */
  virtual ~IDraggable()
  {
  }

};

#endif // IDRAGGABLE_H
