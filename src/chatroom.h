#pragma once
#include "client.h"
#include "constants.h"
#include "raygui.h"
#include "theme.h"
#include <cstring>
#include <raylib.h>
#include <vector>

class ChatRoom {
public:
  ChatRoom(State &state, Font &font_heading, Font &font_text, Client &db);

  void open(const std::string &roomName, const char *user);

  void draw();

private:
  void drawHistory() const;
  void pushWrapped(const std::string &line);
  float textWidth(const char *txt) const;

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
  int roomId_ = -1;

  static constexpr int InLim = 256;
  char input_[InLim + 1]{};

  int colLim_ = 0;
  int rowLim_ = 0;
  float textW;
};
