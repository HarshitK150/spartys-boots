/**
 * @file SensorGate.cpp
 * @author Nitish Maindoliya, Bruno Budelmann
 */

#include "../pch.h"
#include "SensorGate.h"
#include "../Game.h"
#include "../Items/Product.h"
#include "../Items/Sensor.h"
#include "../Visitors/SensorVisitor.h"

/// Size of the SensorGate in pixels
/// @returns the size of the SensorGate
const wxSize SensorGateSize(100, 40);

/// Distance between pin circles and gate
const int DistanceCircleToGate = 20;

/// Default product size in pixels
std::wstring PanelDefaultSize = L"33";

/// Color to use for "red"
const wxColour OhioStateRed = wxColour(187, 0, 0);

/// Color to use for "green"
const wxColour MSUGreen = wxColour(24, 69, 59);

/// Color to use for "blue"
const wxColor UofMBlue = wxColour(0, 39, 76);

/// Mapping from content properties to their associated image
const std::map<Product::Properties, std::wstring> images = {{Product::Properties::Izzo, L"izzo.png"},
                                                            {Product::Properties::Smith, L"smith.png"},
                                                            {Product::Properties::Football, L"football.png"},
                                                            {Product::Properties::Basketball, L"basketball.png"}};

/**
 * Constructor
 * @param game Pointer to the game this sensor gate is part of
 * @param property Pointer to specific property associated with this gate
 */
SensorGate::SensorGate(Game *game, Product::Properties property) : Gate(game), mProperty(property)
{
  // Load the appropriate image for the content
  auto iter = images.find(mProperty);
  if (iter != images.end())
  {
    mSensorImage = GetGame()->GetImage(iter->second);
  }
  AddOutputPin(wxPoint(GetX() + GetWidth() / 2.0 + DefaultLineLength, GetY()));
}

/**
 * Draw the Sensor gate.
 * Override this method to draw the Sensor gate based on the output state.
 * @param gc Graphics context for drawing
 */
void SensorGate::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  Gate::Draw(gc);
  // Save the graphics state
  gc->PushState();

  // Calculate position based on sensor number
  double x = GetX();
  double y = GetY();
  double width = GetWidth();
  double height = GetHeight();
  // Calculate the size of the shape
  double size = std::stod(PanelDefaultSize);

  gc->SetPen(*wxBLACK_PEN);

  // Set the color based on the product's color property for the overlay shapes
  switch (mProperty)
  {
  case Product::Properties::Red:
    gc->SetBrush(wxBrush(OhioStateRed));
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  case Product::Properties::Green:
    gc->SetBrush(wxBrush(MSUGreen));
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  case Product::Properties::Blue:
    gc->SetBrush(wxBrush(UofMBlue));
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  case Product::Properties::Square:
    gc->SetBrush(*wxLIGHT_GREY_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->DrawRectangle(x - size / 2.0, y - size / 2.0, size, size);
    break;
  case Product::Properties::Circle:
    gc->SetBrush(*wxLIGHT_GREY_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->DrawEllipse(x - size / 2.0, y - size / 2.0, size, size);
    break;
  case Product::Properties::Diamond:
    {
      gc->SetBrush(*wxLIGHT_GREY_BRUSH);
      gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
      gc->SetBrush(*wxWHITE_BRUSH);
      // Create a path for a diamond (rotated square)
      wxGraphicsPath path = gc->CreatePath();
      path.MoveToPoint(x, y - size / 2); // Top
      path.AddLineToPoint(x + size / 2, y); // Right
      path.AddLineToPoint(x, y + size / 2); // Bottom
      path.AddLineToPoint(x - size / 2, y); // Left
      path.CloseSubpath();
      gc->DrawPath(path);
      break;
    }
  case Product::Properties::Izzo:
    gc->SetBrush(*wxLIGHT_GREY_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  case Product::Properties::Smith:
    gc->SetBrush(*wxLIGHT_GREY_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  case Product::Properties::Basketball:
    gc->SetBrush(*wxLIGHT_GREY_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  case Product::Properties::Football:
    gc->SetBrush(*wxLIGHT_GREY_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  default:
    gc->SetBrush(*wxWHITE_BRUSH);
    gc->DrawRectangle(x - width / 2.0, y - height / 2.0, width, height);
    break;
  }
  if (mProperty != Product::Properties::None && mSensorImage)
  {
    gc->DrawBitmap(*mSensorImage, x - size / 2.0, y - size / 2.0, size, size);
  }

  // Restore the graphics state
  gc->PopState();
}


/**
 * Compute the output state of the Sensor Gate
 */
void SensorGate::ComputeState()
{
  States state = States::Unknown;

  SensorVisitor visitor(this);
  auto items = GetGame()->GetItems();
  for (auto it = items.rbegin(); it != items.rend(); ++it)
  {
    (*it)->Accept(&visitor);
    if (visitor.IsMatchingProduct())
    {
      state = States::One;
    }
    else
    {
      state = States::Zero;
    }
  }

  SetState(state);

  Gate::ComputeState();
}


/**
 * Get the width of this gate
 * @return Width of this gate
 */
int SensorGate::GetWidth() { return SensorGateSize.GetWidth(); }

/**
 * Get the height of this gate
 * @return Height of this gate
 */
int SensorGate::GetHeight() { return SensorGateSize.GetHeight(); }
