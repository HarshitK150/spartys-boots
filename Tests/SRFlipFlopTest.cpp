/**
 * @file SRFlipFlopTest.cpp
 * @author Harshit Kandpal
 */

#include <pch.h>

#include <regex>
#include <string>
#include <fstream>
#include "gtest/gtest.h"

#include <Game.h>
#include <Gates/SRFlipFlop.h>

using namespace std;

class SRFlipFlopTest : public ::testing::Test
{
protected:
  Game *game;

  void SetUp()
  {
    game = new Game();
  }

  void TestSRFlipFlop(SRFlipFlop *sRFlipFlop, const std::vector<std::vector<States>> &truthTable)
  {
    const auto inputPins = sRFlipFlop->GetInputPins();
    const auto outputPins = sRFlipFlop->GetOutputPins();

    const int numInputPins = inputPins.size();
    const int numOutputPins = outputPins.size();

    for (const auto &row : truthTable)
    {
      for (size_t i = 0; i < numInputPins; i++)
      {
        inputPins[i]->SetState(row[i]);
      }
      sRFlipFlop->ComputeState();

      for (size_t i = 0; i < numOutputPins; i++)
      {
        EXPECT_EQ(outputPins[i]->GetState(), row[numInputPins + i]);
      }
    }
  }
};


TEST_F(SRFlipFlopTest, TestSRFlipFlop)
{
  const std::vector<std::vector<States>> truthTable = {
    {States::Zero, States::Zero, States::Zero, States::One},
    {States::Zero, States::One, States::Zero, States::One},
    {States::One, States::Zero, States::One, States::Zero},
    {States::One, States::One, States::Unknown, States::Unknown},
  };

  TestSRFlipFlop(new SRFlipFlop(game), truthTable);
}