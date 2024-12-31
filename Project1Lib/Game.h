/**
 * @file Game.h
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 *
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "Item.h"
#include "Gates/Sparty.h"
#include "Score.h"

#include <deque>

/**
 * Class that implements a Game
 */
class Game
{
private:
  /// The scale of the game relative to the window
  double mScale = 0;

  /// The offset in X for the game relative to the window
  double mXOffset = 0;

  /// The offset in Y for the game relative to the window
  double mYOffset = 0;

  /// The height of the game in virtual pixels
  int mHeight = 0;

  /// The width of the game in virtual pixels
  int mWidth = 0;

  /// The current level
  int mLevel = 0;

  /// True if ending the level, false otherwise
  bool mEndingLevel = false;
  /// Duration of delay in seconds
  double mEndLevelDelay = 3.0;
  /// True if starting the level, false otherwise
  bool mStartingLevel = false;
  /// Duration of delay in seconds
  double mStartLevelDelay = 6.0;
  /// Time elapsed since the level end message
  double mElapsedTime = 0.0;

  /// Map of images
  std::unordered_map<std::wstring, std::shared_ptr<wxImage>> mImages;

  /// The items in the game
  std::deque<std::shared_ptr<Item>> mItems;

  /// A pointer to the Score object
  Score *mScore;

public:
  Game();

  /**
   * Destructor
   */
  virtual ~Game();

  void OnDraw(const std::shared_ptr<wxGraphicsContext> &graphics, int width, int height);

  void Add(const std::shared_ptr<Item> &item);

  /**
   * Clear the game
   */
  void Clear() { mItems.clear(); }

  void LoadLevel(int level);

  std::shared_ptr<wxImage> GetImage(const std::wstring &filename);

  void Update(double elapsed);
  bool LevelExists(int level);

  void Accept(ItemVisitor *visitor) const;

  std::shared_ptr<IDraggable> HitTest(int x, int y);

  void MoveToFront(Item *item);

  void TryToCatch(OutputPin *outputPin, wxPoint lineEnd);
  void EndLevel();

  /**
   * Getter for the height of the game
   * @return Height of the game in pixels
   */
  int GetHeight() const { return mHeight; }

  /**
   * Getter for the width of the game
   * @return Height of the game in pixels
   */
  int GetWidth() const { return mWidth; }

  /**
   * Getter for the items of the game
   * @return List of items
   */
  std::deque<std::shared_ptr<Item>> GetItems() { return mItems; }

  /**
   * Getter for the X offset of the game
   * @return X offset of the game in pixels
   */
  double GetXOffset() const { return mXOffset; }

  /**
   * Getter for the Y offset of the game
   * @return Y offset of the game in pixels
   */
  double GetYOffset() const { return mYOffset; }

  /**
   * Getter for the scale of the game for virtual pixels
   * @return Scale of the game for virtual pixels
   */
  double GetScale() const { return mScale; }

  /**
   * Getter for the score of the game
   * @return game score
   */
  Score *GetScore() const { return mScore; }
};


#endif // GAME_H
