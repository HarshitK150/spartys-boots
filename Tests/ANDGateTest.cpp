/**
 * @file ANDGateTest.cpp
 * @author Harshit Kandpal
 */

#include <pch.h>

#include <regex>
#include <string>
#include <fstream>
#include "gtest/gtest.h"

#include <Game.h>
#include <Gates/ANDGate.h>

using namespace std;

class ANDGateTest : public ::testing::Test
{
protected:
  Game *game;

  void SetUp()
  {
    game = new Game();
  }

  void TestANDGate(ANDGate *andGate, const std::vector<std::vector<States>> &truthTable)
  {
    const auto inputPins = andGate->GetInputPins();
    const auto outputPins = andGate->GetOutputPins();

    const int numInputPins = inputPins.size();
    const int numOutputPins = outputPins.size();

    for (const auto &row : truthTable)
    {
      for (size_t i = 0; i < numInputPins; i++)
      {
        inputPins[i]->SetState(row[i]);
      }
      andGate->ComputeState();

      for (size_t i = 0; i < numOutputPins; i++)
      {
        EXPECT_EQ(outputPins[i]->GetState(), row[numInputPins + i]);
      }
    }
  }
};


TEST_F(ANDGateTest, TestANDGate)
{
  const std::vector<std::vector<States>> truthTable = {
    {States::Zero, States::Zero, States::Zero},
    {States::Zero, States::One, States::Zero},
    {States::One, States::Zero, States::Zero},
    {States::One, States::One, States::One},
  };

  TestANDGate(new ANDGate(game), truthTable);
}