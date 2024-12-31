/**
 * @file Conveyor.h
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 *
 */

#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "../Item.h"

/**
 * Class that implements a Conveyor
 */
class Conveyor : public Item
{
private:
  /// Boolean for if the conveyor is running or not
  bool mIsRunning = false;

  /// The background image for the conveyor
  std::shared_ptr<wxImage> mConveyorBackgroundImage;
  /// The conveyor belt image
  std::shared_ptr<wxImage> mConveyorBeltImage;
  /// The conveyor panel image (stopped)
  std::shared_ptr<wxImage> mConveyorPanelStoppedImage;
  /// The conveyor panel image (started)
  std::shared_ptr<wxImage> mConveyorPanelStartedImage;

  /// Height of the conveyor
  int mHeight = 0;

  /// X location of the control panel
  double mPanelX = 0;
  /// Y location of the control panel
  double mPanelY = 0;

  /// Speed of the conveyor in Y direction
  int mSpeed = 0;

  /// Current Y Location of the conveyor's moving belt
  double mBeltY = GetY();

public:
  /// Default constructor (disabled)
  Conveyor() = delete;

  /// Copy constructor (disabled)
  Conveyor(const Conveyor &) = delete;

  /// Assignment operator
  void operator=(const Conveyor &) = delete;

  Conveyor(Game *game);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override { visitor->VisitConveyor(this); }

  /**
   * Draw the conveyor
   * @param gc The graphics context to draw on
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  void XmlLoad(wxXmlNode *node) override;

  /**
   * Starts the conveyor
   */
  void Start();

  /**
   * Stops the conveyor
   */
  void Stop();

  /**
   * Handle updates for animation
   * @param elapsed The time since the last update
   */
  void Update(double elapsed) override;

  /**
   * Getter that returns whether the conveyor is running
   * @return true if the conveyor is running, false otherwise
   */
  bool IsRunning() const { return mIsRunning; }

  /**
   * Getter for the conveyor's speed
   * @return The conveyor's speed
   */
  int GetSpeed() const { return mSpeed; }

  /**
   * Getter for the conveyor's height
   * @return The conveyor's height
   */
  bool HitTest(int x, int y) override;

  /**
   * Setter for the conveyor's speed
   * @param x The x speed to set
   * @param y The y speed to set
   */
  void SetPanel(int x, int y)
  {
    mPanelX = x;
    mPanelY = y;
  }

  /**
   * Setter for the conveyor's height
   * @param height The height to set
   */
  void SetHeight(int height) { mHeight = height; }

  /**
   * Setter for the conveyor's speed
   * @param speed The speed to set
   */
  void SetSpeed(int speed) { mSpeed = speed; }
};


#endif // CONVEYOR_H
