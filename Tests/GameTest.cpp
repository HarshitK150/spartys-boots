/**
 * @file GameTest.cpp
 * @author Nitish Maindoliya
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <regex>
#include <string>
#include <fstream>

#include <Game.h>
#include <Item.h>
#include <Items/Scoreboard.h>
#include <Items/Sensor.h>
#include <Items/Conveyor.h>
#include <Gates/Sparty.h>
#include <Gates/Beam.h>

class TestLocationVisitor : public ItemVisitor
{
public:
  void VisitConveyor(Conveyor *conveyor) override
  {
    ASSERT_NE(nullptr, conveyor);
    ASSERT_EQ(150, conveyor->GetX());
    ASSERT_EQ(400, conveyor->GetY());
  }

  void VisitScoreBoard(Scoreboard *scoreboard) override
  {
    ASSERT_NE(nullptr, scoreboard);
    ASSERT_EQ(700, scoreboard->GetX());
    ASSERT_EQ(40, scoreboard->GetY());
  }

  void VisitSensor(Sensor *sensor) override
  {
    // Sensor is not in the XML file
    ASSERT_NE(nullptr, sensor);
  }

  void VisitBeam(Beam *beam) override
  {
    ASSERT_NE(nullptr, beam);
    ASSERT_EQ(242, beam->GetX());
    ASSERT_EQ(437, beam->GetY());
  }

  void VisitSparty(Sparty *sparty) override
  {
    ASSERT_NE(nullptr, sparty);
    ASSERT_EQ(290, sparty->GetX());
    ASSERT_EQ(340, sparty->GetY());
  }
};


class GameTest : public ::testing::Test
{
public:
  void TestItemLocations(Game &game, TestLocationVisitor &visitor) { game.Accept(&visitor); }
};

TEST_F(GameTest, Construct) { Game game; }


TEST_F(GameTest, Load)
{
  Game game;

  game.LoadLevel(0);
  std::deque<std::shared_ptr<Item>> items0 = game.GetItems();

  // Test level 0 - 19 items
  // 18 in the XML file - 1 badge (new feature) and 1 level notice
  ASSERT_EQ(20, items0.size());

  // Test level 1
  game.LoadLevel(1);
  std::deque<std::shared_ptr<Item>> items1 = game.GetItems();
  // 8 in the XML file - 1 badge (new feature) and 1 level notice
  ASSERT_EQ(10, items1.size());

  TestLocationVisitor visitor;
  TestItemLocations(game, visitor);
}
