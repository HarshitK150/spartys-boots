/**
 * @file DFlipFlopTest.cpp
 * @author Harshit Kandpal
 */

#include <pch.h>

#include <regex>
#include <string>
#include <fstream>
#include "gtest/gtest.h"

#include <Game.h>
#include <Gates/DFlipFlop.h>

using namespace std;

class DFlipFlopTest : public ::testing::Test
{
protected:
  Game *game;

  void SetUp()
  {
    game = new Game();
  }

  void TestDFlipFlop(DFlipFlop *dFlipFlop, const std::vector<std::vector<States>> &truthTable)
  {
    const auto inputPins = dFlipFlop->GetInputPins();
    const auto outputPins = dFlipFlop->GetOutputPins();

    const int numInputPins = inputPins.size();
    const int numOutputPins = outputPins.size();

    for (const auto &row : truthTable)
    {
      for (size_t i = 0; i < numInputPins; i++)
      {
        inputPins[i]->SetState(row[i]);
      }
      dFlipFlop->ComputeState();

      for (size_t i = 0; i < numOutputPins; i++)
      {
        EXPECT_EQ(outputPins[i]->GetState(), row[numInputPins + i]);
      }
    }
  }
};


TEST_F(DFlipFlopTest, TestDFlipFlop)
{
  const std::vector<std::vector<States>> truthTable = {
    {States::Zero, States::Zero, States::Zero, States::One},
    {States::Zero, States::One, States::Zero, States::One},
    {States::One, States::Zero, States::Zero, States::One},
    {States::One, States::One, States::One, States::Zero},
  };

  TestDFlipFlop(new DFlipFlop(game), truthTable);
}