#pragma once
#include "client.h"
#include "constants.h"
#include "raygui.h"
#include "theme.h"
#include <cstring>
#include <raylib.h>
#include <vector>

// remeber that sqllite the id index that auto accumulates starts at 1
class ChatRoom {
public:
  ChatRoom(State &state, Font &font_heading, Font &font_text, Client &client);

  void open(const std::string &roomName, const char *user, int room_id);

  void draw();

private:
  void drawHistory() const;
  void pushWrapped(const std::string &line);
  float textWidth(const char *txt) const;
  void check_update();

  State &state_;
  Font &font_heading;
  Font &font_text;
  Client &client_;

  Rectangle historyBox_;
  Rectangle inputBox_;
  Rectangle sendBtn_;
  Rectangle backBtn_;

  std::vector<std::string> history_;
  std::string room_;
  const char *user_ = nullptr;

  static constexpr int InLim = 256;
  char input_[InLim + 1]{};

  int colLim_ = 0;
  int rowLim_ = 0;
  float textW;
  int roomId_ = -100;
  // each room should get a specific range 100 different then the room
  // before it give each room a possible buffer of 100
  // messages that seems fair
  // and then will reserve a id for shit like logn reserve etc...
  // but need a little extra work now when making yur chat rooms
};
