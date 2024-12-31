/**
 * @file Project1App.cpp
 * @author Nitish Maindoliya
 */

#include "pch.h"
#include "Project1App.h"
#include <MainFrame.h>

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#endif

/**
 * Initialize the application.
 * @return
 */
bool Project1App::OnInit()
{
#ifdef WIN32
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  if (!wxApp::OnInit())
  {
    return false;
  }

  // Add image type handlers
  wxInitAllImageHandlers();

  const auto frame = new MainFrame();
  frame->Initialize();
  frame->Show(true);

  return true;
}
