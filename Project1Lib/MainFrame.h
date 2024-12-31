/**
 * @file MainFrame.h
 * @author Nitish Maindoliya
 *
 * The top-level (main) frame of the application
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "GameView.h"

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
  /// View class for our game
  GameView *mGameView = nullptr;

  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &);
  void OnClose(wxCloseEvent &event);

public:
  void Initialize();
};


#endif // MAINFRAME_H
