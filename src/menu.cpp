
#include "menu.h"

Menu::Menu(State &state, Font &font, Db &db)
    : state_{state}, font{font}, db_{db} {
  refreshRooms();
  bounds = {WIDTH * 0.5f - 220, 180, 440, 400};
  textW = MeasureTextEx(font, "MENU", Theme::HeadingSize, Theme::spacing).x;
  constexpr float pad = 32.0f;
  backBtn_ = {pad, 60, 100, 32};
}

void Menu::refreshRooms() {
  rooms_ = db_.get_rooms();

  roomLabels_.clear();
  roomLabels_.reserve(rooms_.size());
  for (const std::string &s : rooms_)
    roomLabels_.push_back(s.c_str());

  rebuildLayout();
}

void Menu::rebuildLayout() {
  cards_.clear();

  const float cx = WIDTH * 0.5f;
  const float firstY = 200.0f;
  const float gapY = Theme::CardH + Theme::Gap;

  for (std::size_t i = 0; i < rooms_.size(); ++i) {
    cards_.push_back(Theme::card(cx, firstY + i * gapY));
  }
}

bool Menu::draw(std::string &outRoom) {
  DrawTextEx(font, "MENU", {WIDTH / 2.0f - textW / 2.0f, 80.f},
             Theme::HeadingSize, Theme::spacing, Theme::Accent);
  if (GuiButton(backBtn_, "Back")) {
    state_ = START;
  }

  if (rooms_.size() <= 8) {
    for (std::size_t i = 0; i < rooms_.size(); ++i) {
      if (GuiButton(cards_[i], rooms_[i].c_str())) {
        outRoom = rooms_[i];
        state_ = ROOM;
        return true;
      }
    }
    return false;
  }

  static int focus = -1;
  static int active = -1;

  int sel = GuiListViewEx(bounds, roomLabels_.data(), roomLabels_.size(),
                          &listScroll_, &focus, &active);
  if (sel != -1) {
    outRoom = rooms_[sel];
    state_ = ROOM;
    return true;
  }

  return false;
}
