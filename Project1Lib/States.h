/**
 * @file States.h
 * @author Nitish Maindoliya
 *
 */

#ifndef PINSTATES_H
#define PINSTATES_H

/**
 * The possible states of a pin
 */
enum class States
{
  One, ///< One state
  Zero, ///< Zero state
  Unknown ///< Unknown state
};

/**
 * The possible types of input pins
 */
enum class InputPinTypes
{
  Regular,
  Set,
  Reset,
  Data,
  Clock
};

/**
 * The possible types of output pins
 */
enum class OutputPinTypes
{
  Regular,
  Inverted
};

#endif // PINSTATES_H
