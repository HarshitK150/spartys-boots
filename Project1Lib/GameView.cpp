/**
 * @file GameView.cpp
 * @author Nitish Maindoliya
 * @author Harshit Kandpal
 */

#include "pch.h"
#include "GameView.h"

#include "Gate.h"
#include "ids.h"
#include "Gates/ORGate.h"
#include "Gates/NOTGate.h"
#include "Gates/ANDGate.h"
#include "Items/Conveyor.h"
#include "Items/Sensor.h"
#include "Score.h"
#include "Gates/DFlipFlop.h"
#include "Gates/SRFlipFlop.h"

/// Frame duration in milliseconds
constexpr int FrameDuration = 30;

/// Initial item X location
constexpr int InitialX = 500;

/// Initial item Y location
constexpr int InitialY = 500;

/// Pixels to increment X and Y location by if an item exists at the current location
constexpr int Increment = 60;


/**
 * Initialize the aquarium view class.
 * @param mainFrame The parent window for this class
 */
void GameView::Initialize(wxFrame *mainFrame)
{
  Create(mainFrame, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
  SetBackgroundStyle(wxBG_STYLE_PAINT);

  Bind(wxEVT_PAINT, &GameView::OnPaint, this);
  Bind(wxEVT_TIMER, &GameView::OnTimer, this);
  Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
  Bind(wxEVT_LEFT_UP, &GameView::OnMouseMove, this);
  Bind(wxEVT_MOTION, &GameView::OnLeftUp, this);


  mTimer.SetOwner(this);
  mTimer.Start(FrameDuration);
  mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent &event)
{
  // Compute the time that has elapsed
  const auto newTime = mStopWatch.Time();
  auto elapsed = (double)(newTime - mTime) * 0.001;
  mTime = newTime;

  // Create a double-buffered display context
  wxAutoBufferedPaintDC dc(this);

  // Clear the image to black
  wxBrush background(*wxBLACK);
  dc.SetBackground(background);
  dc.Clear();

  // Create a graphics context
  auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

  const wxRect rect = GetRect();

  // Tell the game class to update
  mGame.Update(elapsed);

  // Set (or reset) control points
  if (mControlPoints)
  {
    for (const auto &item : mGame.GetItems())
    {
      item->SetControlPoints();
    }
  }
  else
  {
    for (const auto &item : mGame.GetItems())
    {
      item->ResetControlPoints();
    }
  }

  // Tell the game class to draw
  mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Handle a timer event
 * @param event The timer event
 */
void GameView::OnTimer(wxTimerEvent &event) { Refresh(); }

/**
 * Handle a left button mouse press
 * @param event The mouse event
 */
void GameView::OnLeftDown(const wxMouseEvent &event)
{
  // Screen coordinates to virtual coordinates
  const int vX = (event.GetX() - mGame.GetXOffset()) / mGame.GetScale();
  const int vY = (event.GetY() - mGame.GetYOffset()) / mGame.GetScale();

  mGrabbedItem = mGame.HitTest(vX, vY);
  if (mGrabbedItem != nullptr)
  {
    // We grabbed something
    // Move it to the front
    mGrabbedItem->MoveToFront();
    Refresh();
  }
}

/**
 * Handle the left mouse button move event
 * @param event
 */
void GameView::OnMouseMove(const wxMouseEvent &event)
{
  // Screen coordinates to virtual coordinates
  const int vX = (event.GetX() - mGame.GetXOffset()) / mGame.GetScale();
  const int vY = (event.GetY() - mGame.GetYOffset()) / mGame.GetScale();

  // See if an item is currently being moved by the mouse
  if (mGrabbedItem != nullptr)
  {
    // If an item is being moved, we only continue to
    // move it while the left button is down.
    if (event.LeftIsDown())
    {
      mGrabbedItem->SetLocation(vX, vY);
    }
    else
    {
      // When the left button is released, we release the
      // item.
      mGrabbedItem->Release();
      mGrabbedItem = nullptr;
    }

    // Force the screen to redraw
    Refresh();
  }
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftUp(const wxMouseEvent &event) { OnMouseMove(event); }

/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param viewMenu The view menu, so we can add to it if we wish
 * @param levelMenu The level menu, so we can add to it if we wish
 * @param gatesMenu The gates menu, so we can add to it if we wish
 */
void GameView::AddMenus(wxFrame *mainFrame, wxMenu *viewMenu, wxMenu *levelMenu, wxMenu *gatesMenu)
{
  // View menu options
  viewMenu->Append(IDM_VIEW_CONTROL_POINTS, L"&Control Points", L"Enable or disable control points", wxITEM_CHECK);
  mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnViewControlPoints, this, IDM_VIEW_CONTROL_POINTS);
  mainFrame->Bind(wxEVT_UPDATE_UI, &GameView::OnUpdateViewControlPoints, this, IDM_VIEW_CONTROL_POINTS);

  // Level menu options
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_0, L"&Level 0", L"Play Level 0");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_1, L"&Level 1", L"Play Level 1");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_2, L"&Level 2", L"Play Level 2");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_3, L"&Level 3", L"Play Level 3");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_4, L"&Level 4", L"Play Level 4");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_5, L"&Level 5", L"Play Level 5");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_6, L"&Level 6", L"Play Level 6");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_7, L"&Level 7", L"Play Level 7");
  LoadLevelMenuOption(mainFrame, levelMenu, IDM_LEVEL_8, L"&Level 8", L"Play Level 8");

  // Gates menu options
  AddGateMenuOption(mainFrame, gatesMenu, IDM_GATES_AND, L"&AND", L"Add an AND Gate");
  AddGateMenuOption(mainFrame, gatesMenu, IDM_GATES_OR, L"&OR", L"Add an OR Gate");
  AddGateMenuOption(mainFrame, gatesMenu, IDM_GATES_NOT, L"&NOT", L"Add a NOT Gate");
  AddGateMenuOption(mainFrame, gatesMenu, IDM_GATES_SR_FLIP_FLOP, L"&SR Flip Flop", L"Add an SR Flip Flop Gate");
  AddGateMenuOption(mainFrame, gatesMenu, IDM_GATES_D_FLIP_FLOP, L"&D Flip Flop", L"Add a D Flip Flop Gate");
}

/**
 * Menu event handler View>Control Points menu option
 * @param event Menu event
 */
void GameView::OnViewControlPoints(wxCommandEvent &event) { mControlPoints = !mControlPoints; }

/**
 * Update handler for View>Control Points menu option
 * @param event Update event
 */
void GameView::OnUpdateViewControlPoints(wxUpdateUIEvent &event) { event.Check(mControlPoints); }

/**
 * Append an option to the Level menu and bind it to the function GameView::OnLoadLevelMenuOption
 *
 * @param mainFrame The MainFrame object that owns the menu
 * @param menu The Menu we are adding the option to
 * @param id The Menu option ID
 * @param text Text for the menu option
 * @param help Help for the menu option
 */
void GameView::LoadLevelMenuOption(wxFrame *mainFrame, wxMenu *menu, const int id, const std::wstring &text,

                                   const std::wstring &help)
{
  menu->Append(id, text, help);
  mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLoadLevelMenuOption, this, id);
}

/**
 * Handle a Level menu option
 * @param event The menu event
 */
void GameView::OnLoadLevelMenuOption(const wxCommandEvent &event)
{
  const int level = event.GetId() - IDM_LEVEL_0;
  mGame.GetScore()->HardReset();
  mGame.LoadLevel(level);
  Refresh(); // Redraw the view after loading
}

/**
 * Append an option to the Gate menu and bind it to the function GameView::OnAddGateMenuOption
 *
 * @param mainFrame The MainFrame object that owns the menu
 * @param menu The Menu we are adding the option to
 * @param id The Menu option ID
 * @param text Text for the menu option
 * @param help Help for the menu option
 */
void GameView::AddGateMenuOption(wxFrame *mainFrame, wxMenu *menu, const int id, const std::wstring &text,
                                 const std::wstring &help)
{
  menu->Append(id, text, help);
  mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddGateMenuOption, this, id);
}

/**
 * Handle a Gate menu option
 * @param event The menu event
 */
void GameView::OnAddGateMenuOption(const wxCommandEvent &event)
{
  std::shared_ptr<Gate> gate;

  // Add more cases as different gate classes are ready
  switch (event.GetId())
  {
  case IDM_GATES_OR:
    // Uncomment or edit once the Gate and ORGate classes are ready
    gate = std::make_shared<ORGate>(&mGame);
    break;

  case IDM_GATES_NOT:
    gate = std::make_shared<NOTGate>(&mGame);
    break;
  case IDM_GATES_AND:
    gate = std::make_shared<ANDGate>(&mGame);
    break;
  case IDM_GATES_D_FLIP_FLOP:
    gate = std::make_shared<DFlipFlop>(&mGame);
    break;
  case IDM_GATES_SR_FLIP_FLOP:
    gate = std::make_shared<SRFlipFlop>(&mGame);
  }

  if (gate != nullptr)
  {
    int initialX = InitialX;
    int initialY = InitialY;

    for (auto item : mGame.GetItems())
    {
      if (item->GetX() == initialX && item->GetY() == initialY)
      {
        initialX += Increment;
        initialY += Increment;
      }
    }

    gate->SetX(initialX);
    gate->SetY(initialY);
    mGame.Add(gate);
    Refresh();
  }
}
