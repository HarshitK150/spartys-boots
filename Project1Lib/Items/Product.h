/**
 * @file Product.h
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef PRODUCT_H
#define PRODUCT_H
#include "../Game.h"
#include "../XmlLoader.h"

#include <map>


class Conveyor;

/**
 * Class that represents a product.
 */
class Product : public Item
{
public:
  /// The possible product properties.
  /// The None properties allows us to indicate that
  /// the product has no content.
  enum class Properties
  {
    None,
    Red,
    Green,
    Blue,
    White,
    Square,
    Circle,
    Diamond,
    Izzo,
    Smith,
    Football,
    Basketball
  };

  /// The property types
  enum class Types
  {
    Color,
    Shape,
    Content
  };

  /// Mapping from the XML strings for properties to
  /// the Properties enum and the type of the property.
  static const std::map<std::wstring, Properties> NamesToProperties;

  /// Mapping from a property to it's type
  static const std::map<Properties, Types> PropertiesToTypes;

  /// Mapping from content properties to their associated image
  static const std::map<Properties, std::wstring> PropertiesToContentImages;

  /// Default constructor (disabled)
  Product() = delete;

  /// Copy constructor (disabled)
  Product(const Product &) = delete;

  /// Assignment operator (disabled)
  void operator=(const Product &) = delete;

  Product(Game *game, double placement, Properties shape, Properties color, Properties content = Properties::None,
          bool kick = false);

  /**
   * Accept a visitor
   * @param visitor The visitor we accept
   */
  void Accept(ItemVisitor *visitor) override { visitor->VisitProduct(this); }

  /**
   * Draw the product
   * @param gc The graphics context to draw on
   */
  void Draw(const std::shared_ptr<wxGraphicsContext> &gc) override;

  /**
   * Start moving product to the left
   * @param moving True if the product is moving left
   */
  void SetMovingLeft(const bool moving = true) { mMovingLeft = moving; }


  /**
   * Set the product to be moving right
   */
  void HasLeftBeam();

  /**
   * Find whether to kick
   * @return True if the product should be kicked
   */
  bool ShouldKick() const { return mKick; }

  /**
   * Get the placement of the product on the conveyor
   * @return The placement of the product
   */
  double GetPlacement() const { return mPlacement; }

  /**
   * Get the shape of the product
   * @return The shape of the product
   */
  Properties GetShape() const { return mShape; }

  /**
   * Get the color of the product
   * @return The color of the product
   */
  Properties GetColor() const { return mColor; }

  /**
   * Get the content of the product
   * @return The content of the product
   */
  Properties GetContent() const { return mContent; }

  /**
   * Set the placement of the product on the conveyor
   * @param placement The placement of the product
   */
  void SetPlacement(double placement) { mPlacement = placement; }

  /**
   * Set the shape of the product
   * @param shape The shape of the product
   */
  void SetShape(Properties shape) { mShape = shape; }

  /**
   * Set the color of the product
   * @param color The color of the product
   */
  void SetColor(Properties color) { mColor = color; }

  /**
   * Set the content of the product
   * @param content The content of the product
   */
  void SetContent(Properties content) { mContent = content; }

  /**
   * Set whether the product should be kicked
   * @param kick Whether the product should be kicked
   */
  void SetKick(bool kick) { mKick = kick; }

  /**
   * set the product to be the last product on the conveyor
   */
  void SetLast() { mLast = true; }

  /**
   * Get whether the product is the last product on the conveyor
   * @return true if the product is the last product on the conveyor, false otherwise
   */
  bool IsLast() const { return mLast; }

  /**
   * Get whether the product is moving left
   * @return true if the product is moving left, false otherwise
   */
  bool IsMovingLeft() const { return mMovingLeft; }

  /**
   * Get whether this product has hit the beam
   * @return true if the product has hit the beam, false otherwise
   */
  bool GetBeamHit() const { return mBeamHit; }

  /**
   * Set whether this product has hit the beam
   * @param beamHit the value to assigned to beam hit
   */
  void SetBeamHit(bool beamHit) { mBeamHit = beamHit; }

  /// True if the product is currently displayed, false otherwise
  bool mIsCurrentlyDisplayed = true;

private:
  /// The placement of the product on the conveyor
  double mPlacement = 0;
  /// The color of the product
  Properties mColor = Properties::Red;
  /// The shape of the product
  Properties mShape = Properties::Square;
  /// The content of the product
  Properties mContent = Properties::None;
  /// Whether the product should be kicked off the conveyor
  bool mKick = false;
  /// Is the product moving left (after being kicked)?
  bool mMovingLeft = false;
  /// Has the product hit the beam?
  bool mBeamHit = false;
  /// The product image
  std::shared_ptr<wxImage> mProductImage;

  /// True if product is the last product on the conveyor
  bool mLast = false;

  /// Delay after the last product has left the conveyor
  double mLastProductDelay = 0.0;

  /// The size of the product
  double mSize = 80.0;
};


#endif // PRODUCT_H
