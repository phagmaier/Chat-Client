#pragma once
#include "client.h"
#include "constants.h"
#include "raygui.h"
#include "theme.h"
#include <raylib.h>
#include <string>
#include <vector>

class Menu {
public:
  Menu(State &state, Font &font, Client &client);

  // returns true when a room was chosen and writes its name into outRoom
  bool draw(std::string &outRoom);

private:
  void refreshRooms(); // reload DB + recompute geometry
  void rebuildLayout();

  // refs to shared objects
  State &state_;
  Font &font;
  Client &client_;

  // data / layout
  std::vector<std::string> rooms_;
  std::vector<Rectangle> cards_;
  int listScroll_ = 0; // for GuiListView scrolling

  std::vector<const char *> roomLabels_; // <- c-strings for raygui
  float textW;
  Rectangle bounds;
  Rectangle backBtn_;
};
