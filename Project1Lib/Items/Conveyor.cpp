/**
 * @file Conveyor.cpp
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 */

#include "../pch.h"
#include "Conveyor.h"

#include "../Game.h"
#include "Product.h"
#include "../Visitors/ProductAnimator.h"
#include "../Visitors/ZeroScoreVisitor.h"

#include <sstream>


/// Image for the background (base) of the conveyor
const std::wstring ConveyorBackgroundImage = L"conveyor-back.png";

/// Image for the conveyor belt
const std::wstring ConveyorBeltImage = L"conveyor-belt.png";

/// Image for the conveyor control panel when stopped.
const std::wstring ConveyorPanelStoppedImage = L"conveyor-switch-stop.png";

/// Image for the conveyor control panel when started.
const std::wstring ConveyorPanelStartedImage = L"conveyor-switch-start.png";

/// Rectangle representing the location of the start button relative to the panel
/// @return wxRect The rectangle defining the start button's location
const wxRect StartButtonRect(35, 29, 95, 36);

/// Rectangle representing the location of the stop button relative to the panel
/// @return wxRect The rectangle defining the stop button's location
const wxRect StopButtonRect(35, 87, 95, 36);


/**
 * Constructor
 * @param game the game that the conveyor is a part of
 */
Conveyor::Conveyor(Game *game) : Item(game)
{
    mConveyorBackgroundImage = GetGame()->GetImage(ConveyorBackgroundImage);
    mConveyorBeltImage = GetGame()->GetImage(ConveyorBeltImage);
    mConveyorPanelStartedImage = GetGame()->GetImage(ConveyorPanelStartedImage);
    mConveyorPanelStoppedImage = GetGame()->GetImage(ConveyorPanelStoppedImage);
}

/**
 * Draw the conveyor
 * @param gc The graphics context to draw on
 */
void Conveyor::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
    const double height = mHeight;
    const double width = mConveyorBackgroundImage->GetWidth() * height / mConveyorBackgroundImage->GetHeight();

    // Draw conveyor background image
    gc->DrawBitmap(*mConveyorBackgroundImage, GetX() - width / 2, GetY() - height / 2, width, height);

    // Calculate the Y position of the first conveyor image, wrapping it using modulo
    double conveyorY = fmod(mBeltY, height);

    // Draw the first conveyor image
    gc->DrawBitmap(*mConveyorBeltImage, GetX() - width / 2, conveyorY - height, width, height);

    // Draw the second conveyor image within the game area for seamless looping
    gc->DrawBitmap(*mConveyorBeltImage, GetX() - width / 2, conveyorY, width, height);

    // Draw Conveyor Panel (Started is conveyor is running, Stopped otherwise)
    if (mIsRunning)
    {
        gc->DrawBitmap(*mConveyorPanelStartedImage, GetX() + mPanelX, GetY() + mPanelY,
                       mConveyorPanelStartedImage->GetWidth(), mConveyorPanelStartedImage->GetHeight());
    }
    else
    {
        gc->DrawBitmap(*mConveyorPanelStoppedImage, GetX() + mPanelX, GetY() + mPanelY,
                       mConveyorPanelStartedImage->GetWidth(), mConveyorPanelStartedImage->GetHeight());
    }
}


/**
 * Load the attributes specific for a conveyor node.
 * @param node The Xml node we are loading the item from
 */
void Conveyor::XmlLoad(wxXmlNode *node)
{
    XmlLoader loader(GetGame());
    loader.LoadConveyor(this, node);
}


/**
 * Starts the conveyor and returns it
 * to its beginning state
 *
 */
void Conveyor::Start()
{
    mBeltY = 0;
    mIsRunning = true;

    ZeroScoreVisitor zeroScoreVisitor;
    GetGame()->Accept(&zeroScoreVisitor);

    // Reset all products using visitor
    ProductAnimator animator(this, 0, GetGame()->GetHeight(), true);

    auto items = GetGame()->GetItems();
    for (auto item : items)
    {
      item->Accept(&animator);
    }


}

/**
 * Stops the conveyor
 *
 */
void Conveyor::Stop()
{
    mIsRunning = false;
}


/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Conveyor::Update(double elapsed)
{
    if (mIsRunning)
    {
        // Update belt animation
        mBeltY += elapsed * mSpeed;
        if (mBeltY >= mHeight)
        {
            mBeltY = fmod(mBeltY, mHeight);
        }

        // Create animator and apply to all items
        ProductAnimator animator(this, elapsed, GetGame()->GetHeight());
        GetGame()->Accept(&animator);
    }
}

/**
 * Test to see if we hit any buttons on the conveyor, if yes then
 * call the respective functions
 *
 * @param x X location
 * @param y Y location
 * @return False always (so that game does not try to drag conveyor around)
 */
bool Conveyor::HitTest(int x, int y)
{
    // Find relative position of the click with respect to the conveyor panel
    x -= GetX() + mPanelX;
    y -= GetY() + mPanelY;

    // Get the four points of the Start button rectangle
    int x1Start = StartButtonRect.GetX();
    int x2Start = StartButtonRect.GetX() + StartButtonRect.GetWidth();
    int y1Start = StartButtonRect.GetY();
    int y2Start = StartButtonRect.GetY() + StartButtonRect.GetHeight();

    // Get the four points of the Stop button rectangle
    int x1Stop = StopButtonRect.GetX();
    int x2Stop = StopButtonRect.GetX() + StopButtonRect.GetWidth();
    int y1Stop = StopButtonRect.GetY();
    int y2Stop = StopButtonRect.GetY() + StopButtonRect.GetHeight();

    if (x >= x1Start && x <= x2Start && y >= y1Start && y <= y2Start)
    {
        Start();
    }
    else if (x >= x1Stop && x <= x2Stop && y >= y1Stop && y <= y2Stop)
    {
        Stop();
    }

    return false;
}
