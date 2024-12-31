/**
 * @file GameView.h
 * @author Nitish Maindoliya
 *
 *
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"

/**
 * Class that implements a Game Viewer
 */
class GameView : public wxWindow
{
private:
  /// An object of the Game class
  Game mGame;

  /// The timer for the game animation
  wxTimer mTimer;

  /// Stopwatch used to measure elapsed time
  wxStopWatch mStopWatch;

  /// The last stopwatch time
  long mTime = 0;

  /// Any item we are currently dragging
  std::shared_ptr<IDraggable> mGrabbedItem;

  bool mControlPoints = false; ///< Display control points?

  void OnPaint(wxPaintEvent &event);
  void OnTimer(wxTimerEvent &event);
  void OnLeftDown(const wxMouseEvent &event);
  void OnMouseMove(const wxMouseEvent &event);
  void OnLeftUp(const wxMouseEvent &event);
  void OnViewControlPoints(wxCommandEvent &event);
  void OnUpdateViewControlPoints(wxUpdateUIEvent &event);
  void LoadLevelMenuOption(wxFrame *mainFrame, wxMenu *menu, int id, const std::wstring &text,
                           const std::wstring &help);
  void AddGateMenuOption(wxFrame *mainFrame, wxMenu *menu, int id, const std::wstring &text, const std::wstring &help);
  void OnLoadLevelMenuOption(const wxCommandEvent &event);
  void OnAddGateMenuOption(const wxCommandEvent &event);

public:
  void Initialize(wxFrame *mainFrame);

  void AddMenus(wxFrame *mainFrame, wxMenu *viewMenu, wxMenu *levelMenu, wxMenu *gatesMenu);

  /**
   * Stop the timer so the window can close
   */
  void Stop() { mTimer.Stop(); }
};


#endif // GAMEVIEW_H
