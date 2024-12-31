/**
 * @file XmlLoader.cpp
 * @author Anas Shaaban
 */

/**
 * @file XmlLoader.cpp
 * @author Assistant
 */

#include "pch.h"
#include "XmlLoader.h"
#include "Game.h"
#include "Item.h"
#include "Items/Sensor.h"
#include "Gates/Sparty.h"
#include "Gates/SensorGate.h"
#include "Items/Scoreboard.h"
#include "Items/Product.h"
#include "Items/Conveyor.h"
#include "Score.h"
#include <regex>
#include <sstream>

XmlLoader::XmlLoader(Game *game) :
  mGame(game)
{
}

void XmlLoader::LoadItemAttributes(Item *item, wxXmlNode *node)
{
  double x, y;
  node->GetAttribute(L"x", L"0").ToDouble(&x);
  node->GetAttribute(L"y", L"0").ToDouble(&y);
  item->SetX(x);
  item->SetY(y);
}

void XmlLoader::LoadSensor(Sensor *sensor, wxXmlNode *node)
{
  LoadItemAttributes(sensor, node);
  double sensorX = 355; // First sensor gate x position
  double sensorY = 535; // First sensor gate y position

  int sensorNumber = 0;
  for (wxXmlNode *sensorGate = node->GetChildren(); sensorGate != nullptr; sensorGate = sensorGate->GetNext())
  {
    std::shared_ptr<SensorGate> sensorGateItem = nullptr;

    const std::map<std::wstring, Product::Properties> gateTypes = {{L"izzo", Product::Properties::Izzo},
                                                                   {L"smith", Product::Properties::Smith},
                                                                   {L"red", Product::Properties::Red},
                                                                   {L"green", Product::Properties::Green},
                                                                   {L"blue", Product::Properties::Blue},
                                                                   {L"white", Product::Properties::White},
                                                                   {L"square", Product::Properties::Square},
                                                                   {L"diamond", Product::Properties::Diamond},
                                                                   {L"circle", Product::Properties::Circle},
                                                                   {L"football", Product::Properties::Football},
                                                                   {L"basketball", Product::Properties::Basketball},
                                                                   {L"none", Product::Properties::None}};

    std::wstring gateName = sensorGate->GetName().ToStdWstring();
    auto it = gateTypes.find(gateName);
    if (it != gateTypes.end())
    {
      sensorGateItem = std::make_shared<SensorGate>(mGame, it->second);
      sensorGateItem->SetX(sensorX);
      sensorGateItem->SetY(sensorY + sensorNumber * sensorGateItem->GetHeight());
      sensorNumber++;
      mGame->Add(sensorGateItem);
    }
  }
}

void XmlLoader::LoadScoreboard(Scoreboard *scoreboard, wxXmlNode *node)
{
  LoadItemAttributes(scoreboard, node);

  int goodScore;
  int badScore;
  node->GetAttribute(L"good", L"10").ToInt(&goodScore);
  node->GetAttribute(L"bad", L"0").ToInt(&badScore);

  Score *score = scoreboard->GetScore();
  if (score != nullptr)
  {
    score->SetGoodScore(goodScore);
    score->SetBadScore(badScore);
  }

  std::vector<std::string> text;
  for (auto child = node->GetChildren(); child; child = child->GetNext())
  {
    if (child->GetType() == wxXML_TEXT_NODE)
    {
      std::string line = child->GetContent().ToStdString();
      line = std::regex_replace(line, std::regex("\\s+"), " ");
      text.push_back(line);
    }
  }
  scoreboard->SetText(text);
}

void XmlLoader::LoadSparty(Sparty *sparty, wxXmlNode *node)
{
  LoadItemAttributes(sparty, node);

  int height = 0;
  double kickSpeed = 0;
  double kickDuration = 0;
  node->GetAttribute(L"height", L"0").ToInt(&height);
  node->GetAttribute(L"kick-speed", L"0").ToDouble(&kickSpeed);
  node->GetAttribute(L"kick-duration", L"0").ToDouble(&kickDuration);

  sparty->SetHeight(height);
  sparty->SetKickSpeed(kickSpeed);
  sparty->SetKickDuration(kickDuration);

  const std::string pinCoords = node->GetAttribute(L"pin", L"0,0").ToStdString();
  std::istringstream pinStream(pinCoords);
  std::string pinCoord;
  std::vector<int> pin;
  while (std::getline(pinStream, pinCoord, ','))
  {
    pin.push_back(std::stoi(pinCoord));
  }
  sparty->SetPin(pin[0], pin[1]);
}

void XmlLoader::LoadConveyor(Conveyor *conveyor, wxXmlNode *node)
{
  std::shared_ptr<Product> prod;

  LoadItemAttributes(conveyor, node);

  int height = 0;
  int speed = 0;
  node->GetAttribute(L"height", L"0").ToInt(&height);
  node->GetAttribute(L"speed", L"0").ToInt(&speed);

  std::wstring panelCoords = node->GetAttribute(L"panel", "0,0").ToStdWstring();
  std::wstringstream panelStream(panelCoords);
  double panelX, panelY;
  panelStream >> panelX;
  panelStream.ignore();
  panelStream >> panelY;

  conveyor->SetHeight(height);
  conveyor->SetSpeed(speed);
  conveyor->SetPanel(panelX, panelY);

  double lastPlacement = 0;

  for (auto product = node->GetChildren(); product != nullptr; product = product->GetNext())
  {
    if (product->GetName() != "product")
      continue;

    std::wstring placementStr = product->GetAttribute(L"placement", L"0").ToStdWstring();
    double placement;

    if (placementStr[0] == L'+')
    {
      placementStr = placementStr.substr(1);
      double relativeValue;
      std::wstringstream(placementStr) >> relativeValue;
      placement = lastPlacement + relativeValue;
    }
    else
    {
      std::wstringstream(placementStr) >> placement;
    }

    lastPlacement = placement;

    auto shape = Product::NamesToProperties.at(product->GetAttribute(L"shape").ToStdWstring());
    auto color = Product::NamesToProperties.at(product->GetAttribute(L"color").ToStdWstring());
    Product::Properties content = Product::Properties::None;
    if (product->HasAttribute(L"content"))
    {
      content = Product::NamesToProperties.at(product->GetAttribute(L"content").ToStdWstring());
    }

    bool kick = product->GetAttribute(L"kick", L"no") == L"yes";
    prod = std::make_shared<Product>(mGame, placement, shape, color, content, kick);

    prod->SetX(conveyor->GetX());
    prod->SetY(conveyor->GetY() - placement);

    mGame->Add(prod);
  }
  // Last product
  if (prod != nullptr)
  {
    prod->SetLast();
  }
}
