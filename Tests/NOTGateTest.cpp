/**
 * @file NOTGateTest.cpp
 * @author Harshit Kandpal
 */

#include <pch.h>

#include <regex>
#include <string>
#include <fstream>
#include "gtest/gtest.h"

#include <Game.h>
#include <Gates/NOTGate.h>

using namespace std;

class NOTGateTest : public ::testing::Test
{
protected:
  Game *game;

  void SetUp()
  {
    game = new Game();
  }

  void TestNOTGate(NOTGate *notGate, const std::vector<std::vector<States>> &truthTable)
  {
    const auto inputPins = notGate->GetInputPins();
    const auto outputPins = notGate->GetOutputPins();

    const int numInputPins = inputPins.size();
    const int numOutputPins = outputPins.size();

    for (const auto &row : truthTable)
    {
      for (size_t i = 0; i < numInputPins; i++)
      {
        inputPins[i]->SetState(row[i]);
      }
      notGate->ComputeState();

      for (size_t i = 0; i < numOutputPins; i++)
      {
        EXPECT_EQ(outputPins[i]->GetState(), row[numInputPins + i]);
      }
    }
  }
};


TEST_F(NOTGateTest, TestNOTGate)
{
  const std::vector<std::vector<States>> truthTable = {
    {States::Zero, States::One},
    {States::One, States::Zero},
  };

  TestNOTGate(new NOTGate(game), truthTable);
}