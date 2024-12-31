/**
 * @file MainFrame.cpp
 * @author Nitish Maindoliya
 */

#include "pch.h"
#include "MainFrame.h"

/**
 * Initializes the main frame
 */
void MainFrame::Initialize()
{
  Create(nullptr, wxID_ANY, "SpartyBoots", wxDefaultPosition, wxSize(1000, 800));

  // Create a sizer that will lay out child windows
  const auto sizer = new wxBoxSizer(wxVERTICAL);

  /// Create the game view
  mGameView = new GameView();
  mGameView->Initialize(this);

  // Add the game view to the sizer
  sizer->Add(mGameView, 1, wxEXPAND | wxALL);

  SetSizer(sizer);

  Layout();

  const auto menuBar = new wxMenuBar();

  const auto fileMenu = new wxMenu();
  const auto viewMenu = new wxMenu();
  const auto helpMenu = new wxMenu();
  const auto levelMenu = new wxMenu();
  const auto gatesMenu = new wxMenu();

  fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
  helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

  mGameView->AddMenus(this, viewMenu, levelMenu, gatesMenu);

  menuBar->Append(fileMenu, L"&File");
  menuBar->Append(viewMenu, L"&View");
  menuBar->Append(levelMenu, L"&Level");
  menuBar->Append(gatesMenu, L"&Gates");
  menuBar->Append(helpMenu, L"&Help");

  SetMenuBar(menuBar);

  SetStatusBar(new wxStatusBar(this));
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent &event) { Close(true); }

/**
 * Application about box menu handler
 */
void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
  wxMessageBox(L"Sparty's Boots", L"Sparty's Boots\n by\n Team Relay", wxOK | wxCENTRE, this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent &event)
{
  mGameView->Stop();
  Destroy();
}
