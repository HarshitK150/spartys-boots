/**
* @file Sparty.cpp
* @author Nitish Maindoliya
*
*/

#include "../pch.h"
#include "Sparty.h"
#include "../Game.h"
#include "../Items/Product.h"
#include "../Visitors/KickVisitor.h"

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// The maximum rotation for Sparty's boot in radians
const double SpartyBootMaxRotation = 0.8;

/// The point in the kick animation when the product
/// actually is kicked. If the kick duration is 0.25,
/// we kick when 0.25 * 0.35 seconds have elapsed.
const double SpartyKickPoint = 0.35;

/// What percentage of the way down Sparty do we find the tip of his boot?
/// This means the location of the boot when kicking is 80% of the
/// way from the top of the Sparty image.
const double SpartyBootPercentage = 1;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);


/**
 * Constructor
 * @param game Game this item is a member of
 */
Sparty::Sparty(Game *game) :
  Gate(game)
{
}

/**
 * Load the attributes for a Sparty from an XML node
 * @param node The XML node
 */
void Sparty::XmlLoad(wxXmlNode *node)
{
  XmlLoader loader(GetGame());
  loader.LoadSparty(this, node);

  AddInputPin(wxPoint(mPinX - GetX() - DefaultLineLength, mPinY - GetY()));
}

/**
 * Draw the Sparty
 * @param gc The graphics context to draw on
 */
void Sparty::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  Gate::Draw(gc);

  wxColour color;
  switch (GetState())
  {
  case States::Zero:
    color = ConnectionColorZero;
    break;
  case States::One:
    color = ConnectionColorOne;
    break;
  default:
    color = ConnectionColorUnknown;
    break;
  }

  // Draw the Sparty background
  auto spartyBack = GetGame()->GetImage(SpartyBackImage);
  int height = mHeight;
  int width = height * spartyBack->GetWidth() / spartyBack->GetHeight();
  gc->DrawBitmap(*spartyBack, GetX() - width / 2, GetY() - height / 2, width, height);

  // Draw the kicking boot
  DrawBoot(gc, width, height);

  // Define pen for the lines (wires)
  gc->SetPen(wxPen(color, LineWidth));

  // Draw each line segment separately
  gc->StrokeLine(GetX(), GetY(), GetX() + 80, GetY());
  gc->StrokeLine(GetX() + 80, GetY(), GetX() + 80, GetY() - 320);
  gc->StrokeLine(GetX() + 80, GetY() - 320, mPinX, GetY() - 320);
  gc->StrokeLine(mPinX, GetY() - 320, mPinX, mPinY);

  // Draw the background image for Sparty
  gc->DrawBitmap(*spartyBack, GetX() - width / 2, GetY() - height / 2, width, height);

  // Draw the kicking boot with rotation (if any) - this may involve additional calculations for positioning
  DrawBoot(gc, width, height);

  // Draw the Sparty foreground image (SpartyFrontImage)
  auto spartyFront = GetGame()->GetImage(SpartyFrontImage);
  gc->DrawBitmap(*spartyFront, GetX() - width / 2, GetY() - height / 2, width, height);

}

/**
 * Draw the kicking boot with rotation animation
 * @param gc The graphics context
 * @param width The width of Sparty
 * @param height The height of Sparty
 */
void Sparty::DrawBoot(const std::shared_ptr<wxGraphicsContext> &gc, int width, int height)
{
  auto spartyBoot = GetGame()->GetImage(SpartyBootImage);
  int bootWidth = height * spartyBoot->GetWidth() / spartyBoot->GetHeight();
  int bootHeight = height;

  double bootAngle = GetBootRotation();

  // Adjust the boot's position to align it properly with the body
  int bootPosX = GetX() - bootWidth / 2;
  int bootPosY = GetY() + height / 2 - (bootHeight * SpartyBootPercentage); // Adjust the y-position

  // Translate to the pivot point and rotate
  gc->PushState();
  gc->Translate(bootPosX + bootWidth * SpartyBootPivot.m_x, bootPosY + bootHeight * SpartyBootPivot.m_y);
  gc->Rotate(bootAngle);

  // Draw the boot image
  gc->DrawBitmap(*spartyBoot, -bootWidth * SpartyBootPivot.m_x, -bootHeight * SpartyBootPivot.m_y, bootWidth,
                 bootHeight);

  // Restore graphics context state
  gc->PopState();
}


/**
 * Get the boot rotation based on the current kick animation
 * @return The rotation of the boot in radians
 */
double Sparty::GetBootRotation()
{
  if (mKicking)
  {
    // Calculate the kick progress as a fraction of the total kick duration
    double kickProgress = mKickTime / mKickDuration;

    // If the kick is complete, reset the kicking flag and return 0 (no rotation)
    if (kickProgress >= 1.0)
    {
      mKicking = false;
      return 0;
    }

    // Calculate the rotation based on the kick progress
    if (kickProgress < SpartyKickPoint)
    {
      // Boot is moving forward (increasing rotation)
      return SpartyBootMaxRotation * (kickProgress / SpartyKickPoint);
    }
    else
    {
      // Boot is moving backward (decreasing rotation)
      return SpartyBootMaxRotation * (1.0 - (kickProgress - SpartyKickPoint) / (1.0 - SpartyKickPoint));
    }
  }

  // If not kicking, return 0 (no rotation)
  return 0;
}

/**
 * Start the kick animation
 */
void Sparty::Kick()
{
  mKicking = true;
  mKickTime = 0;
}

/**
 * Update the Sparty (for animation and logic)
 * @param elapsed The time since the last update
 */
void Sparty::Update(double elapsed)
{
  Gate::Update(elapsed);

  if (mKicking)
  {
    // Add the elapsed time to the kick timer
    mKickTime += elapsed;

    // Check if we are past the kick point in the animation
    if (mKickTime >= mKickDuration * SpartyKickPoint && !mProductKicked)
    {
      // Normally, we would check for a product to kick here, but for now we skip it
      mProductKicked = true;
    }

    // Stop the kick when the animation is complete
    if (mKickTime >= mKickDuration)
    {
      mKicking = false;
      mProductKicked = false;
      mKickTime = 0; // Reset the kick timer for the next kick
    }
  }
}

/**
 * Kick product from conveyor
 * @param product The product to be kicked
 */
void Sparty::KickProduct(std::shared_ptr<Product> product)
{
  if (!mProductKicked && product)
  {
    //product->MoveLeft(); // Kicks the product to the left by calling its MoveLeft method
    mProductKicked = true; // Ensures only one kick per cycle
  }
}

/**
 * Compute the output state of Sparty
 */
void Sparty::ComputeState()
{
  auto newState = GetInputPins()[0]->GetState();
  if (GetState() != States::One && newState == States::One)
  {
    Kick();
    KickVisitor kickVisitor(this);
    auto items = GetGame()->GetItems();
    for (auto it = items.rbegin(); it != items.rend(); ++it)
    {
      (*it)->Accept(&kickVisitor);
    }
  }
  SetState(newState);
}
