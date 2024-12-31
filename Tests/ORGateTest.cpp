/**
 * @file ORGateTest.cpp
 * @author Harshit Kandpal
 */

#include <pch.h>

#include <regex>
#include <string>
#include <fstream>
#include "gtest/gtest.h"

#include <Game.h>
#include <Gates/ORGate.h>

using namespace std;

class ORGateTest : public ::testing::Test
{
protected:
  Game *game;

  void SetUp()
  {
    game = new Game();
  }

  void TestORGate(ORGate *orGate, const std::vector<std::vector<States>> &truthTable)
  {
    const auto inputPins = orGate->GetInputPins();
    const auto outputPins = orGate->GetOutputPins();

    const int numInputPins = inputPins.size();
    const int numOutputPins = outputPins.size();

    for (const auto &row : truthTable)
    {
      for (size_t i = 0; i < numInputPins; i++)
      {
        inputPins[i]->SetState(row[i]);
      }
      orGate->ComputeState();

      for (size_t i = 0; i < numOutputPins; i++)
      {
        EXPECT_EQ(outputPins[i]->GetState(), row[numInputPins + i]);
      }
    }
  }
};


TEST_F(ORGateTest, TestORGate)
{
  const std::vector<std::vector<States>> truthTable = {
    {States::Zero, States::Zero, States::Zero},
    {States::Zero, States::One, States::One},
    {States::One, States::Zero, States::One},
    {States::One, States::One, States::One},
  };

  TestORGate(new ORGate(game), truthTable);
}