/**
 * @file Item.h
 * @authors Anas Shaban, Nitish Maindoliya
 *
 */

#ifndef ITEM_H
#define ITEM_H

#include "Visitors/ItemVisitor.h"
#include "IDraggable.h"


class OutputPin;
class Game;

class wxXmlNode;

/**
 * Class that implements an Item
 */
class Item : public IDraggable
{
private:
  /// The game this item is contained in.
  Game *mGame;
  /// The x-coordinate of the center of the item.
  double mX = 0;
  /// The y-coordinate of the center of the item.
  double mY = 0;

protected:
  Item(Game *game);

public:
  /// Default constructor (disabled)
  Item() = delete;

  /// Copy constructor (disabled)
  Item(const Item &) = delete;

  /// Assignment operator
  void operator=(const Item &) = delete;

  /// Destructor
  virtual ~Item();

  /**
  * Accept a visitor
  * @param visitor The visitor we accept
  */
  virtual void Accept(ItemVisitor *visitor) = 0;

  /**
   * Getter for the x coordinate
   * @return
   */
  double GetX() const { return mX; };

  /**
   * Setter for the x coordinate
   * @param x
   */
  void SetX(const double x) { mX = x; };

  /**
   * Getter for the y coordinate
   * @return
   */
  double GetY() const { return mY; };

  /**
   * Setter for the y coordinate
   * @param y
   */
  void SetY(const double y) { mY = y; };

  /**
   * Get the game this item is in
   * @return Game pointer
   */
  Game *GetGame() const { return mGame; }

  virtual void Draw(const std::shared_ptr<wxGraphicsContext> &gc);

  /**
   * Test to see if we clicked on some draggable inside the item.
   * @param x X location clicked on
   * @param y Y location clicked on
   * @return Whatever we clicked on or NULL if none
   */
  virtual std::shared_ptr<IDraggable> HitDraggable(int x, int y) { return nullptr; }

  virtual void XmlLoad(wxXmlNode *node);

  /**
   * Test to see if we hit this object with mouse.
   * @param x X position to test
   * @param y Y position to test
   * @return true if hit.
   */
  virtual bool HitTest(int x, int y) { return false; }

  /**
   * Handle updates for animation
   * @param elapsed The time since the last update
   */
  virtual void Update(double elapsed)
  {
  }

  /**
   * Handle a left button mouse press
   * @param x X location
   * @param y Y location
   */
  virtual void OnLeftDown(int x, int y)
  {
  }

  /**
   * Set the location of the item
   * @param x X location in pixels
   * @param y Y location in pixels
   */
  void SetLocation(double x, double y) override
  {
    mX = x;
    mY = y;
  }

  /**
   * Move this item to the front
   * of the list of items.
   */
  void MoveToFront() override
  {
  }

  /**
   * Release after moving
   */
  void Release() override
  {
  }

  /**
   * Try to catch an input pin at the new x,y location of the wire end
   * @param outputPin Output pin we are trying to catch from
   * @param wireEnd The wire end point
   * @return true if caught
   */
  virtual bool Catch(OutputPin *outputPin, wxPoint wireEnd) { return false; }

  /**
   * Set the control points associated with this item
   */
  virtual void SetControlPoints()
  {
  }

  /**
   * Reset the control points associated with this item
   */
  virtual void ResetControlPoints()
  {
  }
};

#endif // ITEM_H
