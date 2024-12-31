/**
 * @file VisitorTest.cpp
 * @author Shashank Singh
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Items/Badge.h>
#include <Items/Conveyor.h>
#include <Visitors/ItemVisitor.h>
#include <Items/LevelNotice.h>
#include <Items/Product.h>
#include <Items/Scoreboard.h>
#include <Items/Sensor.h>
#include <Gates/ANDGate.h>
#include <Gates/Beam.h>
#include <Gates/DFlipFlop.h>
#include <Gates/NOTGate.h>
#include <Gates/ORGate.h>
#include <Gates/SensorGate.h>
#include <Gates/Sparty.h>
#include <Gates/SRFlipFlop.h>

class TestVisitor : public ItemVisitor
{
public:
  int mNumBadges = 0;
  void VisitBadge(Badge *badge) override { mNumBadges++; }

  int mNumConveyors = 0;
  void VisitConveyor(Conveyor *conveyor) override { mNumConveyors++; }

  int mNumLevelNotices = 0;
  void VisitLevelNotice(LevelNotice *levelNotice) override { mNumLevelNotices++; }

  int mNumProducts = 0;
  void VisitProduct(Product *product) override { mNumProducts++; }

  int mNumScoreboards = 0;
  void VisitScoreBoard(Scoreboard *scoreboard) override { mNumScoreboards++; }

  int mNumSensors = 0;
  void VisitSensor(Sensor *sensor) override { mNumSensors++; }

  int mNumAndGates = 0;
  void VisitANDGate(ANDGate *ANDgate) override { mNumAndGates++; }

  int mNumBeams = 0;
  void VisitBeam(Beam *beam) override { mNumBeams++; }

  int mNumDFlipFlops = 0;
  void VisitDFlipFlop(DFlipFlop *dFlipFlop) override{ mNumDFlipFlops++; }

  int mNumNotGates = 0;
  void VisitNOTGate(NOTGate *NOTgate) override { mNumNotGates++; }

  int mNumOrGates = 0;
  void VisitORGate(ORGate *ORgate) override { mNumOrGates++; }

  int mNumSensorGates = 0;
  void VisitSensorGate(SensorGate *Sensorgate) override { mNumSensorGates++; }

  int mNumSpartys = 0;
  void VisitSparty(Sparty *sparty) override { mNumSpartys++; }

  int mNumSRFlipFlops = 0;
  void VisitSRFlipFlop(SRFlipFlop *srFlipFlop) override{ mNumSRFlipFlops++; }
};

TEST (VisitorTest, ItemVisitor)
{
  /// Ensures that no additional visit functions are called on game level 0.

  /**
   * Game constuctor automatically loads level 0
   * which has 1 sensor, 7 Sensor Gates, 1 Conveyor
   * 6 Products, 1 beam, 1 sparty, 1 level notice & 1 Badge
   *
   * Empty test ensures nothing else is visited
   */
  Game emptyGame;
  emptyGame.LoadLevel(0);
  TestVisitor emptyVisitor;
  emptyGame.Accept(&emptyVisitor);

  ASSERT_EQ(1, emptyVisitor.mNumBadges) << L"Visitor number of Badges";
  ASSERT_EQ(1, emptyVisitor.mNumConveyors) << L"Visitor number of Conveyors";
  ASSERT_EQ(1, emptyVisitor.mNumLevelNotices) << L"Visitor number of Level Notices";
  ASSERT_EQ(6, emptyVisitor.mNumProducts) << L"Visitor number of Products";
  ASSERT_EQ(1, emptyVisitor.mNumScoreboards) << L"Visitor number of Scoreboards";
  ASSERT_EQ(1, emptyVisitor.mNumSensors) << L"Visitor number of Sensors";
  ASSERT_EQ(0, emptyVisitor.mNumAndGates) << L"Visitor number of AND Gates";
  ASSERT_EQ(1, emptyVisitor.mNumBeams) << L"Visitor number of Beams";
  ASSERT_EQ(0, emptyVisitor.mNumDFlipFlops) << L"Visitor number of D Flip Flop Gates";
  ASSERT_EQ(0, emptyVisitor.mNumNotGates) << L"Visitor number of NOT Gates";
  ASSERT_EQ(0, emptyVisitor.mNumOrGates) << L"Visitor number of OR Gates";
  ASSERT_EQ(7, emptyVisitor.mNumSensorGates) << L"Visitor number of Sensor Gates";
  ASSERT_EQ(1, emptyVisitor.mNumSpartys) << L"Visitor number of Spartys";
  ASSERT_EQ(0, emptyVisitor.mNumSRFlipFlops) << L"Visitor number of SR Flip Flop Gates";

  /// Ensures each visitor function works correctly

  // Construct a game object
  Game game1;
  game1.LoadLevel(0);

  // Add some items of each type
  auto badge = std::make_shared<Badge>(&game1);
  auto conveyor = std::make_shared<Conveyor>(&game1);
  auto levelNotice = std::make_shared<LevelNotice>(&game1, 0, true);
  auto product = std::make_shared<Product>(&game1, 100 , Product::Properties::Square, Product::Properties::Green, Product::Properties::Izzo);
  auto scoreboard = std::make_shared<Scoreboard>(&game1, game1.GetScore());
  auto sensor = std::make_shared<Sensor>(&game1);
  auto andGate = std::make_shared<ANDGate>(&game1);
  auto beam = std::make_shared<Beam>(&game1);
  auto dFlipFlop = std::make_shared<DFlipFlop>(&game1);
  auto notGate = std::make_shared<NOTGate>(&game1);
  auto orGate = std::make_shared<ORGate>(&game1);
  auto sensorGate = std::make_shared<SensorGate>(&game1, Product::Properties::None);
  auto sparty = std::make_shared<Sparty>(&game1);
  auto srFlipFlop = std::make_shared<SRFlipFlop>(&game1);

  game1.Add(badge);
  game1.Add(conveyor);
  game1.Add(levelNotice);
  game1.Add(product);
  game1.Add(scoreboard);
  game1.Add(sensor);
  game1.Add(andGate);
  game1.Add(beam);
  game1.Add(dFlipFlop);
  game1.Add(notGate);
  game1.Add(orGate);
  game1.Add(sensorGate);
  game1.Add(sparty);
  game1.Add(srFlipFlop);

  TestVisitor visitor;
  game1.Accept(&visitor);

  ASSERT_EQ(2, visitor.mNumBadges) << L"Visitor number of Badges"; //< 2
  ASSERT_EQ(2, visitor.mNumConveyors) << L"Visitor number of Conveyors";
  ASSERT_EQ(2, visitor.mNumLevelNotices) << L"Visitor number of Level Notices";
  ASSERT_EQ(7, visitor.mNumProducts) << L"Visitor number of Products";
  ASSERT_EQ(2, visitor.mNumScoreboards) << L"Visitor number of Scoreboards";
  ASSERT_EQ(2, visitor.mNumSensors) << L"Visitor number of Sensors";
  ASSERT_EQ(1, visitor.mNumAndGates) << L"Visitor number of AND Gates";
  ASSERT_EQ(2, visitor.mNumBeams) << L"Visitor number of Beams";
  ASSERT_EQ(1, visitor.mNumDFlipFlops) << L"Visitor number of D Flip Flop Gates";
  ASSERT_EQ(1, visitor.mNumNotGates) << L"Visitor number of NOT Gates";
  ASSERT_EQ(1, visitor.mNumOrGates) << L"Visitor number of OR Gates";
  ASSERT_EQ(8, visitor.mNumSensorGates) << L"Visitor number of Sensor Gates";
  ASSERT_EQ(2, visitor.mNumSpartys) << L"Visitor number of Spartys";
  ASSERT_EQ(1, visitor.mNumSRFlipFlops) << L"Visitor number of SR Flip Flop Gates";
}