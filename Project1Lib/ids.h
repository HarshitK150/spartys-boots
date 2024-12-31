/**
* @file ids.h
 *
 * @author Harshit Kandpal
 *
 * ID values for menus and other controls
 */

#ifndef GAME_IDS_H
#define GAME_IDS_H

/**
 * Menu id values
 */
enum IDs
{
  /// View>Control Points menu option
  IDM_VIEW_CONTROL_POINTS = wxID_HIGHEST + 1,

  /// Level>Level 0 menu option
  IDM_LEVEL_0,

  /// Level>Level 1 menu option
  IDM_LEVEL_1,

  /// Level>Level 2 menu option
  IDM_LEVEL_2,

  /// Level>Level 3 menu option
  IDM_LEVEL_3,

  /// Level>Level 4 menu option
  IDM_LEVEL_4,

  /// Level>Level 5 menu option
  IDM_LEVEL_5,

  /// Level>Level 6 menu option
  IDM_LEVEL_6,

  /// Level>Level 7 menu option
  IDM_LEVEL_7,

  /// Level>Level 8 menu option
  IDM_LEVEL_8,

  /// Gates>AND menu option
  IDM_GATES_AND,

  /// Gates>OR menu option
  IDM_GATES_OR,

  /// Gates>NOT menu option
  IDM_GATES_NOT,

  /// Gates>SR Flip Flop menu option
  IDM_GATES_SR_FLIP_FLOP,

  /// Gates>D Flip Flop menu option
  IDM_GATES_D_FLIP_FLOP,

  /// Debug> Beam
  IDM_DEBUG_BEAM,

  /// Debug> Sparty
  IDM_DEBUG_SPARTY,

  /// Debug> Conveyor
  IDM_DEBUG_CONVEYOR,

  /// Debug> Sensor
  IDM_DEBUG_SENSOR,

  /// Debug> Scoreboard
  IDM_DEBUG_SCOREBOARD,

  /// Debug> Beginning Level Notice
  IDM_DEBUG_LEVEL_BEGIN_NOTICE,

  /// Debug> Level Notice
  IDM_DEBUG_LEVEL_NOTICE,

  /// Debug> End Level
  IDM_DEBUG_END_LEVEL
};

#endif //GAME_IDS_H
