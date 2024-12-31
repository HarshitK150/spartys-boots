/**
 * @file Beam.cpp
 * @author Nitish Maindoliya
 * @author Anas Shaaban
 */

#include "../pch.h"
#include "Beam.h"
#include "../Game.h"
#include "../Visitors/BeamProductVisitor.h"


/// Image for the beam sender and receiver when red
const std::wstring BeamRedImage = L"beam-red.png";

/// Image for the beam sender and receiver when green
const std::wstring BeamGreenImage = L"beam-green.png";

/// X offset for the beam pin in pixels
/// This is larger than normal to get it past Sparty's feet
const int BeamPinOffset = 80;

/// Default length of line from the pin
static const int PinLength = 20;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown = wxColour(128, 128, 128);


/**
 * Constructor
 * @param game the game that the Beam is a part of
 */
Beam::Beam(Game *game) :
  Gate(game)
{
  // Load the images
  mBeamRedImage = GetGame()->GetImage(BeamRedImage);
  mBeamGreenImage = GetGame()->GetImage(BeamGreenImage);
  mActiveBeamImage = mBeamGreenImage; // Start with green
  mBeamBroken = false;
}

/**
 * Load the beam from an XML node
 * @param node the XML node
 */
void Beam::XmlLoad(wxXmlNode *node)
{
  Item::XmlLoad(node);
  node->GetAttribute(L"sender", L"0").ToInt(&mSender);
}


/**
 * Set the beam broken state
 * @param broken True if beam is broken
 */
void Beam::SetBeamBroken(bool broken)
{
  mBeamBroken = broken;
  SetState(broken ? States::One : States::Zero);
}

/**
 * Draw the beam
 * @param gc the graphics context to draw on
 */
void Beam::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  // Draw gate components first
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

  mActiveBeamImage = mBeamBroken ? mBeamRedImage : mBeamGreenImage;

  // Draw the glowing line
  wxPen laser1(wxColour(255, 200, 200, 100), 8);
  wxPen laser2(wxColour(255, 0, 0, 175), 4);

  double centerY = GetY() - mActiveBeamImage->GetHeight() / 2 + mActiveBeamImage->GetHeight() / 2;

  gc->SetPen(laser1);
  gc->StrokeLine(GetX() - mActiveBeamImage->GetWidth() / 2, centerY, GetX() + mSender, centerY);

  gc->SetPen(laser2);
  gc->StrokeLine(GetX() - mActiveBeamImage->GetWidth() / 2, centerY, GetX() + mSender, centerY);

  // Draw the receivers
  gc->DrawBitmap(mActiveBeamImage->Mirror(), GetX() - mActiveBeamImage->GetWidth() / 2,
                 GetY() - mActiveBeamImage->GetHeight() / 2, mActiveBeamImage->GetWidth(),
                 mActiveBeamImage->GetHeight());

  gc->DrawBitmap(*mActiveBeamImage, GetX() + mSender - mActiveBeamImage->GetWidth() / 2,
                 GetY() - mActiveBeamImage->GetHeight() / 2, mActiveBeamImage->GetWidth(),
                 mActiveBeamImage->GetHeight());

  // Draw the line to the pin
  wxPen BeamPinLine(color, 3);
  gc->SetPen(BeamPinLine);
  gc->StrokeLine(GetX() + mActiveBeamImage->GetWidth() / 2, GetY(), GetX() + BeamPinOffset, GetY());

  AddOutputPin(wxPoint(mActiveBeamImage->GetWidth() / 2 + BeamPinOffset - PinLength, 0));
}

/**
 * Compute the state of the beam
 */
void Beam::ComputeState()
{
  // First reset the state
  SetBeamBroken(false);

  if (auto game = GetGame())
  {
    BeamProductVisitor visitor(this);
    game->Accept(&visitor);

    if (visitor.FoundIntersection())
    {
      SetBeamBroken(true);
    }
  }

  Gate::ComputeState();
}
