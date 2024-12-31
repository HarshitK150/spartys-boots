/**
 * @file Item.cpp
 * @authors Anas Shaban, Nitish Maindoliya
 */

#include "pch.h"
#include "Item.h"

/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game) :
  mGame(game)
{
}

/**
 * Destructor
 */
Item::~Item() = default;

/**
 * Draw the item
 * @param gc The graphics context to draw on
 */
void Item::Draw(const std::shared_ptr<wxGraphicsContext> &gc)
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
  node->GetAttribute(L"x", L"0").ToDouble(&mX);
  node->GetAttribute(L"y", L"0").ToDouble(&mY);
}
