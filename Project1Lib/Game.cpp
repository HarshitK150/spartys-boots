/**
 * @file Game.cpp
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 */

#include "pch.h"

#include "Game.h"

#include "Gates/Beam.h"
#include "Gates/Sparty.h"
#include "Items/Badge.h"
#include "Items/Conveyor.h"
#include "Items/LevelNotice.h"
#include "Items/Scoreboard.h"
#include "Items/Sensor.h"
#include "Visitors/LevelScoreUpdateVisitor.h"

#include <sstream>

/// Directory containing level files
const std::wstring LevelsDirectory = L"resources/levels/";

/// Directory containing image files
const std::wstring ImageDirectory = L"resources/images/";

/**
 * Game constructor
 */
Game::Game()
{
  // Initialize the Score object
  mScore = new Score();

  // Load the first level
  LoadLevel(1);
};

/**
 * Game destructor
 */
Game::~Game()
{
  // Clean up the Score object
  delete mScore;
}

/**
 * Draw the game
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void Game::OnDraw(const std::shared_ptr<wxGraphicsContext> &graphics, const int width, const int height)
{
  // Determine the size of the playing area in pixels
  const int pixelWidth = mHeight;
  const int pixelHeight = mWidth;

  //
  // Automatic Scaling
  //
  const auto scaleX = double(width) / double(pixelWidth);
  const auto scaleY = double(height) / double(pixelHeight);
  mScale = std::min(scaleX, scaleY);

  mXOffset = (width - pixelWidth * mScale) / 2.0;
  mYOffset = 0;
  if (height > pixelHeight * mScale)
  {
    mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
  }

  graphics->PushState();

  graphics->Translate(mXOffset, mYOffset);
  graphics->Scale(mScale, mScale);

  graphics->Clip(0, 0, pixelWidth, pixelHeight); // Clip to the game window's dimensions

  // Draw background
  wxBrush background(wxColour(0xE6, 0xFF, 0xE6));
  graphics->SetBrush(background);
  graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);

  // Reset the pen to remove any outlines
  graphics->SetPen(*wxTRANSPARENT_PEN);

  // Draw in layers:
  // 1. First draw non-product, non-beam items
  for (const auto &item : mItems)
  {
    if (!dynamic_cast<Product *>(item.get()) && !dynamic_cast<Beam *>(item.get()))
    {
      item->Draw(graphics);
    }
  }

  // 2. Draw beams
  for (const auto &item : mItems)
  {
    if (dynamic_cast<Beam *>(item.get()))
    {
      item->Draw(graphics);
    }
  }

  // 3. Finally draw products on top
  for (const auto &item : mItems)
  {
    if (dynamic_cast<Product *>(item.get()))
    {
      item->Draw(graphics);
    }
  }

  graphics->PopState();
}

/**
 * Add item to the game
 * @param item Item to add
 */
void Game::Add(const std::shared_ptr<Item> &item) { mItems.push_back(item); }

/**
 * Load a level from a file
 * @param level Level to load
 */
void Game::LoadLevel(const int level)
{
  mLevel = level;
  wxXmlDocument xmlDoc;
  auto filename = LevelsDirectory + L"level" + std::to_wstring(level) + L".xml";

  if (!xmlDoc.Load(filename))
  {
    return;
  }

  Clear();

  // Get root and size
  auto root = xmlDoc.GetRoot();
  std::wstring sizeStr = root->GetAttribute(L"size", L"100,100").ToStdWstring();
  std::wstringstream sizeStream(sizeStr);
  wchar_t comma;
  sizeStream >> mHeight >> comma >> mWidth;

  // Process items
  for (auto node = root->GetChildren()->GetChildren(); node; node = node->GetNext())
  {
    std::shared_ptr<Item> item = nullptr;
    auto name = node->GetName();

    // Create appropriate item type
    if (name == L"sensor")
    {
      item = std::make_shared<Sensor>(this);
    }
    else if (name == L"conveyor")
    {
      item = std::make_shared<Conveyor>(this);
    }
    else if (name == L"beam")
    {
      item = std::make_shared<Beam>(this);
    }
    else if (name == L"sparty")
    {
      item = std::make_shared<Sparty>(this);
    }
    else if (name == L"scoreboard")
    {
      item = std::make_shared<Scoreboard>(this, mScore);
    }

    // Add and load item if created
    if (item != nullptr)
    {
      Add(item);
      mItems.back()->XmlLoad(node);
    }
  }

  // Add the badge
  const auto badge = std::make_shared<Badge>(this);
  badge->UpdateBadge(mScore);
  Add(badge);

  /// Display the Level begin message
  Add(std::make_shared<LevelNotice>(this, level, true));
}


/**
 * Get an image from the image map
 * @param filename Filename of the image
 * @return Image
 */
std::shared_ptr<wxImage> Game::GetImage(const std::wstring &filename)
{
  const auto it = mImages.find(filename);
  if (it == mImages.end())
  {
    auto image = std::make_shared<wxImage>(ImageDirectory + filename);

    if (!image->IsOk())
    {
      wxMessageBox(L"Failed to load image: " + filename, L"Error", wxICON_ERROR);
      return nullptr;
    }

    mImages[filename] = image;
    return image;
  }

  return it->second;
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor *visitor) const
{
  for (const auto& item : mItems)
  {
    item->Accept(visitor);
  }
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
 */
std::shared_ptr<IDraggable> Game::HitTest(int x, int y)
{
  for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
  {
    // Did we click on something contained in the drawable?
    if (auto draggable = (*i)->HitDraggable(x, y); draggable != nullptr)
    {
      return draggable;
    }

    if ((*i)->HitTest(x, y))
    {
      return *i;
    }
  }

  return nullptr;
}

/**
 * Move an item to the front of the list of items.
 *
 * Removes item from the list and adds it to the end so it
 * will display last.
 * @param item The item to move
 */
void Game::MoveToFront(Item *item)
{
  // Find the shared_ptr corresponding to rawPtr
  auto loc =
    std::find_if(mItems.begin(), mItems.end(), [item](std::shared_ptr<Item> ptr) { return ptr.get() == item; });
  auto itemPtr = *loc;
  if (loc != end(mItems))
  {
    mItems.erase(loc);
  }

  mItems.push_back(itemPtr);
}

/**
 * Try to catch an input pin at the new x,y location of the wire end
 * @param outputPin Output pin we are trying to catch from
 * @param lineEnd The line end point
 */
void Game::TryToCatch(OutputPin *outputPin, wxPoint lineEnd)
{
  for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
  {
    if ((*i)->Catch(outputPin, lineEnd))
    {
      return;
    }
  }
}

/**
 * Ends the current game level
 */
void Game::EndLevel()
{
  // Set the end flag
  mEndingLevel = true;
  // Set the start flag
  mStartingLevel = true;
  // Reset elapsed time
  mElapsedTime = 0.0;
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
  if (mEndingLevel)
  {
    mElapsedTime += elapsed;

    if (mElapsedTime >= mEndLevelDelay)
    {
      mEndingLevel = false;
      /// Display the Level end message
      Add(std::make_shared<LevelNotice>(this, mLevel, false));

      // Update Game and Level Scores
      LevelScoreUpdateVisitor levelScoreUpdateVisitor;
      Accept(&levelScoreUpdateVisitor);
    }
  }

  if (mStartingLevel)
  {
    mElapsedTime += elapsed;

    if (mElapsedTime >= mStartLevelDelay)
    {
      mStartingLevel = false;
      if (LevelExists(mLevel + 1))
      {
        LoadLevel(mLevel + 1);
      }
      else
      {
        LoadLevel(mLevel);
      }
    }
  }

  for (auto item : mItems)
  {
    item->Update(elapsed);
  }
}

/**
 * Returns if a level exists or not
 * @param level The level we are checking if it exists or not
 * @return True if the level exists, false otherwise
 */
bool Game::LevelExists(int level)
{
  wxString filename = LevelsDirectory + L"level" + std::to_wstring(level) + L".xml";
  return wxFileExists(filename);
}