/**
 * @file ItemVisitor.h
 *
 * @author Shashank Singh
 *
 * Item visitor base class.
 */

#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H

// Forward references to all Item types
class Badge;
class Conveyor;
class LevelNotice;
class Product;
class Scoreboard;
class Sensor;
class ANDGate;
class Beam;
class DFlipFlop;
class NOTGate;
class ORGate;
class SensorGate;
class Sparty;
class SRFlipFlop;
class Gate;

/**
 * Item visitor base class
 */
class ItemVisitor
{
protected:
  /**
   * Constructor
   * Ensures this is an abstract class
   */
  ItemVisitor()
  {
  }

public:
  /// Destructor
  virtual ~ItemVisitor()
  {
  }

  /**
   * Visit a Badge object
   * @param badge Badge we are visiting
   */
  virtual void VisitBadge(Badge *badge)
  {
  }

  /**
   * Visit a conveyor object
   * @param conveyor Conveyor we are visiting
   */
  virtual void VisitConveyor(Conveyor *conveyor)
  {
  }

  /**
   * Visit a LevelNotice object
   * @param levelNotice LevelNotice object we are visiting
   */
  virtual void VisitLevelNotice(LevelNotice *levelNotice)
  {
  }

  /**
   * Visit a Product object
   * @param product Product object we are visiting
   */
  virtual void VisitProduct(Product *product)
  {
  }

  /**
   * Visit a Scoreboard object
   * @param scoreboard Scoreboard object we are visiting
   */
  virtual void VisitScoreBoard(Scoreboard *scoreboard)
  {
  }

  /**
   * Visit a Sensor object
   * @param sensor Sensor object we are visiting
   */
  virtual void VisitSensor(Sensor *sensor)
  {
  }

  /**
   * Visit a ANDGate object
   * @param ANDgate ANDGate object we are visiting
   */
  virtual void VisitANDGate(ANDGate *ANDgate)
  {
  }

  /**
   * Visit a Beam object
   * @param beam Beam object we are visiting
   */
  virtual void VisitBeam(Beam *beam)
  {
  }

  /**
   * Visit a DFlipFlop object
   * @param dFlipFlop DFlipFlop object we are visiting
   */
  virtual void VisitDFlipFlop(DFlipFlop *dFlipFlop)
  {
  }

  /**
   * Visit a NOTGate object
   * @param NOTgate NOTGate object we are visiting
   */
  virtual void VisitNOTGate(NOTGate *NOTgate)
  {
  }

  /**
   * Visit a ORGate object
   * @param ORgate ORGate object we are visiting
   */
  virtual void VisitORGate(ORGate *ORgate)
  {
  }

  /**
   * Visit a SensorGate object
   * @param Sensorgate SensorGate object we are visiting
   */
  virtual void VisitSensorGate(SensorGate *Sensorgate)
  {
  }

  /**
   * Visit a Sparty object
   * @param sparty Sparty object we are visiting
   */
  virtual void VisitSparty(Sparty *sparty)
  {
  }

  /**
   * Visit a SRFlipFlop object
   * @param srFlipFlop SRFlipFlop object we are visiting
   */
  virtual void VisitSRFlipFlop(SRFlipFlop *srFlipFlop)
  {
  }

  /**
   * Visit all gates
   * @param gate Gate object we are visiting
   */
  virtual void VisitGates(Gate *gate) {}


};

#endif // ITEMVISITOR_H
