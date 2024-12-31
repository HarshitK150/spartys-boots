/**
* @file XmlLoader.h
 * @author Anas Shaaban
 *
 *
 */

/**
 * @file XmlLoader.h
 * @author Anas Shaaban
 *
 *
 */

#ifndef PROJECT1_XMLLOADER_H
#define PROJECT1_XMLLOADER_H

#include <wx/xml/xml.h>


// Forward declarations
class Game;
class Item;
class Sensor;
class Sparty;
class Scoreboard;
class Conveyor;
class Score;
class Product;

/**
 * Class to handle XML loading operations for game items
 */
class XmlLoader {
private:
  /// The game this loader is associated with
  Game* mGame;

public:
  /**
   * Constructor
   * @param game The game this loader is associated with
   */
  explicit XmlLoader(Game* game);

  /**
   * Load basic item attributes from XML node
   * @param item Item to load attributes into
   * @param node XML node to load from
   */
  void LoadItemAttributes(Item* item, wxXmlNode* node);

  /**
   * Load sensor attributes from XML node
   * @param sensor Sensor to load attributes into
   * @param node XML node to load from
   */
  void LoadSensor(Sensor* sensor, wxXmlNode* node);

  /**
   * Load sparty attributes from XML node
   * @param sparty Sparty to load attributes into
   * @param node XML node to load from
   */
  void LoadSparty(Sparty* sparty, wxXmlNode* node);

  /**
   * Load scoreboard attributes from XML node
   * @param scoreboard Scoreboard to load attributes into
   * @param node XML node to load from
   */
  void LoadScoreboard(Scoreboard* scoreboard, wxXmlNode* node);

  /**
   * Load conveyor attributes from XML node
   * @param conveyor Conveyor to load attributes into
   * @param node XML node to load from
   */
  void LoadConveyor(Conveyor* conveyor, wxXmlNode* node);
};

#endif //PROJECT1_XMLLOADER_H

