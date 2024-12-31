/**
 * @file Product.cpp
 * @author Nitish Maindoliya
 */

#include "../pch.h"
#include "Product.h"

#include "Conveyor.h"
#include "../Visitors/ScoreVisitor.h"

/// Default product size in pixels
std::wstring ProductDefaultSize = L"80";

/// Size to draw content relative to the product size
double ContentScale = 0.8;

/// Color to use for "red"
/// @return the color
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green"
/// @return the color
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue"
/// @return the color
const wxColor UofMBlue(0, 39, 76);

/// Delay after last product has left beam or
/// been kicked before we end the level.
const double LastProductDelay = 3;


/// Mapping from the XML strings for properties to
const std::map<std::wstring, Product::Properties> Product::NamesToProperties = {
  {L"red", Product::Properties::Red},           {L"green", Product::Properties::Green},
  {L"blue", Product::Properties::Blue},         {L"white", Product::Properties::White},
  {L"square", Product::Properties::Square},     {L"circle", Product::Properties::Circle},
  {L"diamond", Product::Properties::Diamond},   {L"izzo", Product::Properties::Izzo},
  {L"smith", Product::Properties::Smith},       {L"basketball", Product::Properties::Basketball},
  {L"football", Product::Properties::Football}, {L"none", Product::Properties::None},
};

/// Mapping from a property to it's type
const std::map<Product::Properties, Product::Types> Product::PropertiesToTypes = {
  {Product::Properties::Red, Product::Types::Color},          {Product::Properties::Green, Product::Types::Color},
  {Product::Properties::Blue, Product::Types::Color},         {Product::Properties::White, Product::Types::Color},
  {Product::Properties::Square, Product::Types::Shape},       {Product::Properties::Circle, Product::Types::Shape},
  {Product::Properties::Diamond, Product::Types::Shape},      {Product::Properties::Izzo, Product::Types::Content},
  {Product::Properties::Smith, Product::Types::Content},      {Product::Properties::Football, Product::Types::Content},
  {Product::Properties::Basketball, Product::Types::Content}, {Product::Properties::None, Product::Types::Content}};


/// Mapping from content properties to their associated image
const std::map<Product::Properties, std::wstring> Product::PropertiesToContentImages = {
  {Product::Properties::Izzo, L"izzo.png"},
  {Product::Properties::Smith, L"smith.png"},
  {Product::Properties::Football, L"football.png"},
  {Product::Properties::Basketball, L"basketball.png"}};

/**
 * Constructor
 * @param game The game this product is a member of
 * @param placement The placement of the product on the conveyor
 * @param shape The shape of the product
 * @param color The color of the product
 * @param content The content of the product
 * @param kick True if the product should be kicked off the conveyor
 */
Product::Product(Game *game, double placement, Properties shape, Properties color, Properties content, bool kick) :
    Item(game), mPlacement(placement), mShape(shape), mColor(color), mContent(content), mKick(kick)
{
  // Load content image if there is content
  if (content != Properties::None)
  {
    auto iter = PropertiesToContentImages.find(content);
    if (iter != PropertiesToContentImages.end())
    {
      mProductImage = GetGame()->GetImage(iter->second);
    }
  }
}

/**
 * Draw the product
 * @param gc The graphics context to draw on
 */
void Product::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
  if (!mIsCurrentlyDisplayed)
    return;

  // Save the graphics state
  gc->PushState();

  // Set transparent pen for no outlines
  gc->SetPen(*wxTRANSPARENT_PEN);

  // Set the color based on the product's color property
  switch (mColor)
  {
  case Properties::Red:
    gc->SetBrush(wxBrush(OhioStateRed));
    break;
  case Properties::Green:
    gc->SetBrush(wxBrush(MSUGreen));
    break;
  case Properties::Blue:
    gc->SetBrush(wxBrush(UofMBlue));
    break;
  default:
    gc->SetBrush(*wxWHITE_BRUSH);
    break;
  }

  // Calculate the center position
  double centerX = GetX();
  double centerY = GetY();
  double size = std::stod(ProductDefaultSize);

  // Draw the shape
  switch (mShape)
  {
  case Properties::Square:
    gc->DrawRectangle(centerX - size / 2, centerY - size / 2, size, size);
    break;
  case Properties::Circle:
    gc->DrawEllipse(centerX - size / 2, centerY - size / 2, size, size);
    break;
  case Properties::Diamond:
    {
      // Create a path for a diamond (rotated square)
      wxGraphicsPath path = gc->CreatePath();
      path.MoveToPoint(centerX, centerY - size*sqrt(2) / 2); // Top
      path.AddLineToPoint(centerX + size*sqrt(2) / 2, centerY); // Right
      path.AddLineToPoint(centerX, centerY + size*sqrt(2) / 2); // Bottom
      path.AddLineToPoint(centerX - size*sqrt(2) / 2, centerY); // Left
      path.CloseSubpath();
      gc->DrawPath(path);
      break;
    }
  default:
    break;
  }

  // Draw the content image if it exists
  if (mContent != Properties::None && mProductImage)
  {
    double contentSize = size * ContentScale;
    double contentX = centerX - contentSize / 2;
    double contentY = centerY - contentSize / 2;
    gc->DrawBitmap(*mProductImage, contentX, contentY, contentSize, contentSize);
  }

  // Restore the graphics state
  gc->PopState();
}

/**
 * Start moving product to the left
 */
void Product::HasLeftBeam()
{
  if (mLast)
  {
    GetGame()->EndLevel();
  }

  // Update score
  ScoreVisitor scoreVisitor(this);
  GetGame()->Accept(&scoreVisitor);
}
